from dataclasses import dataclass
import torch
import torch.nn as nn
import math
from torch.nn import functional as F
import inspect
from transformers import LlamaForCausalLM, AutoTokenizer
# -----------------------------------------------------------------------------------------------
class LlamaSdpaAttention(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.q_proj = nn.Linear(config.embedding_dim, config.att_heads * config.head_dim, bias=False)
        self.k_proj = nn.Linear(config.embedding_dim, config.kv_heads * config.head_dim, bias=False)
        self.v_proj = nn.Linear(config.embedding_dim, config.kv_heads * config.head_dim, bias=False)
        self.o_proj = nn.Linear(config.att_heads * config.head_dim, config.embedding_dim, bias=False)
    
    def forward(self, x, position_embeddings):
        pass
    


class LlamaMLP(nn.Module):
    pass


class LlamaRotaryEmbedding(nn.Module):
    def __init__(self, head_dim, base):
        super().__init__()
        self.head_dim = head_dim
        self.base = base
        
        ids = torch.arange(0, self.head_dim // 2, dtype=torch.float)
        theta = torch.pow(self.base, -2 * ids / self.head_dim)

        self.register_buffer('theta', theta, persistent=False)

    def forward(self, hidden_state):
        _, sequence_length, _ = hidden_state.shape
        position = torch.arange(0, sequence_length, dtype=torch.float32).unsqueeze(-1)

        embeddings = position * self.theta
        sin_embeddings = torch.sin(embeddings)
        cos_embeddings = torch.cos(embeddings)

        sin_embeddings = sin_embeddings.repeat(1, 2)
        cos_embeddings = cos_embeddings.repeat(1, 2)

        return cos_embeddings, sin_embeddings

class LlamaRMSNorm(nn.Module):
    def __init__(self, embedding_dim, eps=1e-6):
        super().__init__()
        self.eps = eps
        self.gamma = nn.Parameter(torch.ones(embedding_dim)) # learning parametre γ
    
    def forward(self, x):
        '''
        input: (batch, sequence_length, embedding_size)
        algorithm:
            RMS(x) = sqrt(mean(x_i^2) + epsilon)
            norm_x = (x / RMS(x)) * gamma
        output: (batch, sequence_length, embedding_size)
        '''
        RMS = torch.sqrt(torch.mean(x**2, dim=-1, keepdim=True) + self.eps)
        out = x / RMS * self.gamma
        return out
    pass


class LlamaDecoderLayer(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.self_attn = LlamaSdpaAttention(config)
        self.mlp = LlamaMLP()
        self.input_layernorm = LlamaRMSNorm(config.embedding_dim)
        self.post_attention_layernorm = LlamaRMSNorm(config.embedding_dim)

    def forward(self, x, position_embeddings):
        residual = x
        x = self.input_layernorm(x)
        x = self.self_attn(x, position_embeddings)
        x = residual + x
        
        residual = x
        x = self.post_attention_layernorm(x)
        x = self.mlp(x)
        x = residual + x
        
        return x
        
#------------------------------------------------------------------------------------------------
@dataclass
class LLaMA3Config:
    vocab_size: int = 32000
    embedding_dim: int = 2048
    layer_num: int = 6 
    head_dim: int = 256
    att_heads: int = 8
    kv_heads: int = 2
    base: int = 10000



class LLaMA3(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.embed_tokens = nn.Embedding(config.vocab_size, config.embedding_dim)
        self.layers = nn.ModuleList([LlamaDecoderLayer(config) for _ in range(config.layer_num)])
        self.LlamaRotaryEmbedding = LlamaRotaryEmbedding(config.head_dim, config.base)
        self.norm = LlamaRMSNorm(config.embedding_dim)
    
    def forward(self, x):
        embeddings = self.embed_tokens(x)
        position_embeddings = self.LlamaRotaryEmbedding(x)
        x = self.layers(embeddings, position_embeddings)


#------------------------------------------------------------------------------------------------

Rope_layer = LlamaRotaryEmbedding(8, 10000)
torch.manual_seed(42)
hidden_state = torch.randint(0, 10, (1, 4, 8))
cos, sin = Rope_layer(hidden_state)
print("1, 4, 8:")
print(cos)
print(sin)