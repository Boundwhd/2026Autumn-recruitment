from dataclasses import dataclass
import torch
import torch.nn as nn
import math
from torch.nn import functional as F
import inspect
from transformers import LlamaForCausalLM, AutoTokenizer

# -----------------------------------------------------------------------------------------------
def rotate_half(x):
    x1 = x[..., : x.shape[-1] // 2]
    x2 = x[..., x.shape[-1] // 2 :]
    return torch.cat((-x2, x1), dim=-1)


def apply_Rope(q, k, cos, sin):
    cos = cos.unsqueeze(1)
    sin = sin.unsqueeze(1)

    q_embd = q * cos + (rotate_half(q) * sin)
    k_embd = k * cos + (rotate_half(k) * sin)

    return q_embd, k_embd

class LlamaSdpaAttention(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.head_dim = config.head_dim
        self.num_key_value_groups = config.att_heads // config.kv_heads
        self.q_proj = nn.Linear(config.embedding_dim, config.att_heads * config.head_dim, bias=False)
        self.k_proj = nn.Linear(config.embedding_dim, config.kv_heads * config.head_dim, bias=False)
        self.v_proj = nn.Linear(config.embedding_dim, config.kv_heads * config.head_dim, bias=False)
        self.o_proj = nn.Linear(config.att_heads * config.head_dim, config.embedding_dim, bias=False)
    
    def forward(self, hidden_states, position_embeddings):
        input_shape = hidden_states.shape[:-1]
        hidden_shape = (*input_shape, -1, self.head_dim)

        query_states = self.q_proj(hidden_states).view(hidden_shape).transpose(1, 2)
        key_states   = self.k_proj(hidden_states).view(hidden_shape).transpose(1, 2)
        value_states = self.v_proj(hidden_states).view(hidden_shape).transpose(1, 2)

        cos, sin = position_embeddings
        query_states, key_states = apply_Rope(query_states, key_states, cos, sin)

        key_states = key_states.repeat_interleave(self.num_key_value_groups, dim=1)
        value_states = value_states.repeat_interleave(self.num_key_value_groups, dim=1)

        attn_output = torch.nn.functional.scaled_dot_product_attention(
            query_states,  
            key_states,    
            value_states,  
            is_causal=True  
        )

        attn_output = attn_output.transpose(1, 2).contiguous()  
        attn_output = attn_output.view(*input_shape, -1) 
        attn_output = self.o_proj(attn_output)

        return attn_output

class LlamaMLP(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.embedding_dim = config.embedding_dim
        self.intermediate_size = config.intermediate_size
        self.gate_proj = nn.Linear(self.embedding_dim, self.intermediate_size, bias=False)
        self.up_proj = nn.Linear(self.embedding_dim, self.intermediate_size, bias=False)
        self.down_proj = nn.Linear(self.intermediate_size, self.embedding_dim, bias=False)
        self.act_fn = nn.SiLU()

    def forward(self, hidden_states):
        down_proj = self.down_proj(self.act_fn(self.gate_proj(hidden_states)) * self.up_proj(hidden_states))
        return down_proj


class LlamaRotaryEmbedding(nn.Module):
    def __init__(self, head_dim, base):
        super().__init__()
        self.head_dim = head_dim
        self.base = base
        
        ids = torch.arange(0, self.head_dim // 2, dtype=torch.float)
        theta = torch.pow(self.base, -2 * ids / self.head_dim)

        self.register_buffer('theta', theta, persistent=False)

    def forward(self, x):
        batch_size, sequence_length, _ = x.shape
        position = torch.arange(0, sequence_length, dtype=torch.float32).unsqueeze(-1)

        embeddings = position * self.theta
        sin_embeddings = torch.sin(embeddings)
        cos_embeddings = torch.cos(embeddings)

        sin_embeddings = sin_embeddings.repeat(1, 2).unsqueeze(0)
        cos_embeddings = cos_embeddings.repeat(1, 2).unsqueeze(0)

        sin_embeddings = sin_embeddings.repeat(batch_size, 1, 1)
        cos_embeddings = cos_embeddings.repeat(batch_size, 1, 1)

        return cos_embeddings, sin_embeddings

class LlamaRMSNorm(nn.Module):
    def __init__(self, embedding_dim, eps=1e-6):
        super().__init__()
        self.eps = eps
        self.gamma = nn.Parameter(torch.ones(embedding_dim)) # learning parametre γ
    
    def forward(self, hidden_states):
        RMS = torch.sqrt(torch.mean(hidden_states**2, dim=-1, keepdim=True) + self.eps)
        out = hidden_states / RMS * self.gamma
        return out


class LlamaDecoderLayer(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.self_attn = LlamaSdpaAttention(config)
        self.mlp = LlamaMLP(config)
        self.input_layernorm = LlamaRMSNorm(config.embedding_dim)
        self.post_attention_layernorm = LlamaRMSNorm(config.embedding_dim)

    def forward(self, hidden_states, position_embeddings):
        residual = hidden_states
        hidden_states = self.input_layernorm(hidden_states)
        hidden_states = self.self_attn(hidden_states, position_embeddings)
        hidden_states = residual + hidden_states
        
        residual = hidden_states
        hidden_states = self.post_attention_layernorm(hidden_states)
        hidden_states = self.mlp(hidden_states)
        hidden_states = residual + hidden_states
        
        return hidden_states
        
#------------------------------------------------------------------------------------------------
@dataclass
class LLaMA3Config:
    vocab_size: int = 500
    embedding_dim: int = 2048
    layer_num: int = 16 
    head_dim: int = 256
    att_heads: int = 8
    kv_heads: int = 8
    base: int = 10000
    intermediate_size: int = 8192


class LLaMA3(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.num_hidden_layers = config.layer_num
        self.embed_tokens = nn.Embedding(config.vocab_size, config.embedding_dim)
        self.layers = nn.ModuleList([LlamaDecoderLayer(config) for _ in range(config.layer_num)])
        self.LlamaRotaryEmbedding = LlamaRotaryEmbedding(config.head_dim, config.base)
        self.norm = LlamaRMSNorm(config.embedding_dim)
    
    def forward(self, x):
        hidden_states = self.embed_tokens(x)
        position_embeddings = self.LlamaRotaryEmbedding(hidden_states)

        for decoder_layer in self.layers[: self.num_hidden_layers]:
            hidden_states = decoder_layer(hidden_states, position_embeddings)
        
        return hidden_states


#------------------------------------------------------------------------------------------------

config = LLaMA3Config()
model = LLaMA3(config)
print(model)
inputs = torch.randint(0, 500, (2, 32))
out = model(inputs)
print(out.shape)