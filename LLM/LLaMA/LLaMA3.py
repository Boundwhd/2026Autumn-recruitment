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
        self.o_proj = nn.Linear(config.embedding_dim, config.kv_heads * config.head_dim, bias=False)
        self.rotary_emb = LlamaRotaryEmbedding()
    pass


class LlamaMLP(nn.Module):
    pass


class LlamaRotaryEmbedding(nn.Module):
    def __init__(self):
        super().__init__()
    
    def forward(self, hidden_state):
        batch_size, sequence_length, embedding_size = hidden_state.shape




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

    def forward(self, x):
        residual = x
        x = self.input_layernorm(x)
        x = self.self_attn(x)
        x = residual + x
        
        residual = x
        x = self.post_attention_layernorm(x)
        x = self.mlp(x)
        x = residual + x
        
        return x
        
#------------------------------------------------------------------------------------------------
@dataclass
class LLaMA3Config:
    vocab_size: int = 200
    embedding_dim: int = 32
    layer_num: int = 1 
    head_dim: int = 8
    att_heads: int = 4
    kv_heads: int = 1



class LLaMA3(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.embed_tokens = nn.Embedding(config.vocab_size, config.embedding_dim)
        self.layers = nn.ModuleList([LlamaDecoderLayer(config) for _ in range(config.layer_num)])
        self.LlamaRotaryEmbedding = LlamaRotaryEmbedding()
        self.norm = LlamaRMSNorm(config.embedding_dim)
    pass


#------------------------------------------------------------------------------------------------


config = LLaMA3Config()
model = LLaMA3(config)
print(model)