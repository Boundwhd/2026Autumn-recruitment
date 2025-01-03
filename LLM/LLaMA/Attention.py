import torch
import torch.nn as nn
from typing import Optional
import math

class LLaMAconfig:
    def __init__(
        self,
        embedding_size: int = 2048,                 # 词嵌入特征维度
        num_layers: int = 32,                       # decoder数量
        num_attention_heads: int = 8,               # 多头注意力头数   
        num_intermediate_size: int = 2048 * 4,      # 前馈层大小（MLP中使用）
        sequence_length: int = 512,                 # 序列长度
        attention_dropout: float = 0.0,             # 注意力dropout率
        num_key_value_heads: int = 1                # 分组注意力查询机制
    ):
        self.embedding_size = embedding_size
        self.num_layers = num_layers
        self.num_attention_heads = num_attention_heads
        self.num_intermediate_size = num_intermediate_size
        self.sequence_length = sequence_length
        self.attention_dropout = attention_dropout
        self.num_key_value_heads = num_key_value_heads      # 分组查询注意力机制
    pass
'''
RMSNorm归一化层
'''



'''
WwiGLU激活函数
'''


class RotaryEmbedding(nn.Module):
    '''
    旋转位置编码，给定序列长度和特征数，输出cos和sin位置编码特征，后续与query，key矩阵对应乘
    '''
    def __init__(self, config: LLaMAconfig):
        super().__init__()
        self.config = config
        self.sequence_length = self.config.sequence_length
        self.embedding_size = self.config.embedding_size // self.config.num_attention_heads
    def forward(self):
        position = torch.arange(0, self.sequence_length, dtype=torch.float).unsqueeze(-1)
        ids = torch.arange(0, self.embedding_size // 2, dtype=torch.float)
        theta = torch.pow(10000, -2 * ids / self.embedding_size)
        
        # sequence * embedding_size / 2
        embedding = position * theta
        sin_embedding = torch.sin(embedding).transpose(1, 0)
        sin_embedding = torch.cat([sin_embedding, sin_embedding], dim=0)
        sin_embedding = sin_embedding.transpose(1, 0).unsqueeze(0)
        # [theta0, theta1, ..., theta0, theta1, ...]
        
        cos_embedding = torch.cos(embedding).transpose(1, 0)
        cos_embedding = torch.cat([cos_embedding, cos_embedding], dim=0)
        cos_embedding = cos_embedding.transpose(1, 0).unsqueeze(0)
        
        return cos_embedding, sin_embedding

def rotate_half(x):
    """Rotates half the hidden dims of the input."""
    x1 = x[..., : x.shape[-1] // 2]
    x2 = x[..., x.shape[-1] // 2 :]
    return torch.cat((-x2, x1), dim=-1)

def apply_rotary_pos_emb(q, k, cos, sin):
    
    cos = cos.unsqueeze(1)
    sin = sin.unsqueeze(1)
    q_embed = (q * cos) + (rotate_half(q) * sin)
    k_embed = (k * cos) + (rotate_half(k) * sin)
    return q_embed, k_embed

def repeat_kv(hidden_states: torch.Tensor, n_rep: int) -> torch.Tensor:
    """
    This is the equivalent of torch.repeat_interleave(x, dim=1, repeats=n_rep). The hidden states go from (batch,
    num_key_value_heads, seqlen, head_dim) to (batch, num_attention_heads, seqlen, head_dim)
    """
    batch, num_key_value_heads, slen, head_dim = hidden_states.shape
    if n_rep == 1:
        return hidden_states
    hidden_states = hidden_states[:, :, None, :, :].expand(batch, num_key_value_heads, n_rep, slen, head_dim)
    return hidden_states.reshape(batch, num_key_value_heads * n_rep, slen, head_dim)

class Attention(nn.Module):
    
    def __init__(self, config: LLaMAconfig, layer_idx: Optional[int] = None):
        super().__init__()
        self.config = config
        self.layer_idx = layer_idx
        
        self.attention_dropout = config.attention_dropout
        self.hidden_size = config.embedding_size
        self.num_heads = config.num_attention_heads
        self.head_dim = self.hidden_size // self.num_heads
        self.num_key_value_heads = config.num_key_value_heads
        self.num_key_value_groups = self.num_heads // self.num_key_value_heads
        
        self.q_proj = nn.Linear(self.hidden_size, self.num_heads * self.head_dim, bias=False)               
        self.k_proj = nn.Linear(self.hidden_size, self.num_key_value_heads * self.head_dim, bias=False)
        self.v_proj = nn.Linear(self.hidden_size, self.num_key_value_heads * self.head_dim, bias=False)
        self.o_proj = nn.Linear(self.num_heads * self.head_dim, self.hidden_size, bias=False)
        
        self.rotary_emb = RotaryEmbedding(self.config)
        
    def forward(
        self,
        hidden_states: torch.Tensor,
        position_embeddings: Optional[tuple[torch.Tensor, torch.Tensor]] = None
    ) -> torch.Tensor:
        bsz, q_len, _ = hidden_states.size()
        
        query_states = self.q_proj(hidden_states)
        key_states = self.k_proj(hidden_states)
        value_states = self.v_proj(hidden_states)
        
        # (bsz, sqz_len, embedding_dim)
        '''
        query维度是：        'nums_head * head_dim'
        key和value维度是：   'nums_key_value_head * head_dim' 对应分组   
        '''
        query_states = query_states.view(bsz, q_len, -1, self.head_dim).transpose(1, 2)
        key_states = key_states.view(bsz, q_len, -1, self.head_dim).transpose(1, 2)
        value_states = value_states.view(bsz, q_len, -1, self.head_dim).transpose(1, 2)
        
        # (bsz, nums_head, sqz_len, head_dim)
        # (bsz, nums_kv_head, sqz_len, head_dim)
        '''
        具体的实现与公式上不同，公式中是相邻的两个特征一正一负，具体的实现是前一半为正后一半为负
        不一定要严格按照相邻两两组合旋转，神经元是无序的，不依赖维度顺序
        '''
        cos, sin = position_embeddings
        query_states, key_states = apply_rotary_pos_emb(query_states, key_states, cos, sin)
        
        '''
        K/V矩阵GQA，MHA，MQA
        '''
        key_states = repeat_kv(key_states, self.num_key_value_groups)
        value_states = repeat_kv(value_states, self.num_key_value_groups)
        attn_weights = torch.matmul(query_states, key_states.transpose(2, 3)) / math.sqrt(self.head_dim)
        attn_weights = nn.functional.softmax(attn_weights, dim=-1, dtype=torch.float32).to(query_states.dtype)
        attn_output = torch.matmul(attn_weights, value_states)
        
        '''内存连续'''
        attn_output = attn_output.transpose(1, 2).contiguous()
        '''合并多头特征'''
        attn_output = attn_output.reshape(bsz, q_len, -1)
        
        attn_output = self.o_proj(attn_output)

        return attn_output
        

if __name__ == "__main__":
    pass
    
    
    
    
    
        
