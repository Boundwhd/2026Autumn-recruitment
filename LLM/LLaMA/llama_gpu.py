#---------------------------------------------------------------------------------------------------------------------
# Config
import torch
import torch.nn as nn
import torch.nn.functional as F
import math
from dataclasses import dataclass

'''
Llama config
'''
@dataclass
class LLaMA3Config:
    vocab_size: int = 32000         
    embedding_dim: int = 2048
    layer_num: int = 3
    head_dim: int = 256
    att_heads: int = 8
    kv_heads: int = 2
    base: int = 10000
    intermediate_size: int = 8192
#---------------------------------------------------------------------------------------------------------------------
# Model
'''
Attention:
1. RoPE Apply.
2. Grouped-Query Attention.
3. Flash attention.
'''
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

def repeat_kv(hidden_states, num_rep):
    batch, kv_heads, sequence_length, head_dim = hidden_states.shape
    if num_rep == 1:
        return hidden_states
    hidden_states = hidden_states[:, :, None, :, :].expand(batch, kv_heads, num_rep, sequence_length, head_dim)
    return hidden_states.reshape(batch, kv_heads * num_rep, sequence_length, head_dim)

class LlamaAttention(nn.Module):
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

        key_states = repeat_kv(key_states, self.num_key_value_groups)
        value_states = repeat_kv(value_states, self.num_key_value_groups)
        
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
    
'''
RoPE:
1. Precompute theta and store it in the buffer, reduce the computational load.
'''
class LlamaRotaryEmbedding(nn.Module):
    def __init__(self, head_dim, base):
        super().__init__()
        self.head_dim = head_dim
        self.base = base
        
        ids = torch.arange(0, self.head_dim // 2, dtype=torch.float)
        theta = torch.pow(self.base, -2 * ids / self.head_dim)

        self.register_buffer('theta', theta, persistent=False)

    def forward(self, x):
        device = x.device
        batch_size, sequence_length, _ = x.shape
        position = torch.arange(0, sequence_length, dtype=torch.float32).unsqueeze(-1).to(device)

        embeddings = position * self.theta
        cos_embeddings = torch.cos(embeddings)
        sin_embeddings = torch.sin(embeddings)
        
        cos_embeddings = cos_embeddings.repeat(1, 2).unsqueeze(0)
        sin_embeddings = sin_embeddings.repeat(1, 2).unsqueeze(0)
        
        cos_embeddings = cos_embeddings.repeat(batch_size, 1, 1)
        sin_embeddings = sin_embeddings.repeat(batch_size, 1, 1)
        
        return cos_embeddings, sin_embeddings
    
'''
RMSNorm:
'''
class LlamaRMSNorm(nn.Module):
    def __init__(self, embedding_dim, eps=1e-6):
        super().__init__()
        self.eps = eps
        self.gamma = nn.Parameter(torch.ones(embedding_dim)) # learning parametre γ
    
    def forward(self, hidden_states):
        RMS = torch.sqrt(torch.mean(hidden_states**2, dim=-1, keepdim=True) + self.eps)
        out = hidden_states / RMS * self.gamma
        return out
    
'''
MLP:
1. Use the SiLU activation function.
2. Two encoder and one decoder. One of the encoder use SiLU activation.
'''
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
    
class LlamaDecoderLayer(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.self_attn = LlamaAttention(config)
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
    
'''
Main Branch of LLAMA
'''
class LLaMA3(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.num_hidden_layers = config.layer_num
        self.embed_tokens = nn.Embedding(config.vocab_size, config.embedding_dim)
        self.layers = nn.ModuleList([LlamaDecoderLayer(config) for _ in range(config.layer_num)])
        self.LlamaRotaryEmbedding = LlamaRotaryEmbedding(config.head_dim, config.base)
        self.norm = LlamaRMSNorm(config.embedding_dim)
        self.lm_head = nn.Linear(config.embedding_dim, config.vocab_size, bias=False)
    
    def forward(self, ids, targets=None):
        hidden_states = self.embed_tokens(ids)
        position_embeddings = self.LlamaRotaryEmbedding(hidden_states)

        for decoder_layer in self.layers[: self.num_hidden_layers]:
            hidden_states = decoder_layer(hidden_states, position_embeddings)
        
        hidden_states = self.norm(hidden_states)
        logits = self.lm_head(hidden_states)

        loss = None
        if targets is not None:
            loss = F.cross_entropy(logits.view(-1, logits.size(-1)), targets.view(-1))
        return logits, loss


#------------------------------------------------------------------------------
# Main

device = 'cuda' if torch.cuda.is_available() else 'cpu'
config = LLaMA3Config()

print(torch.__version__)
print(torch.cuda.is_available())  # 确保 PyTorch 识别到了 GPU
print(torch.backends.cuda.matmul.allow_tf32)  # 检查是否允许 TF32 计算










