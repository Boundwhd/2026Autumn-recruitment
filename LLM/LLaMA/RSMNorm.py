import torch
import torch.nn as nn
from transformers import LlamaModel


class RMSNorm(torch.nn.Module):
    def __init__(self, dim: int, eps: float = 1e-6):
        super().__init__()
        self.eps = eps
        self.weight = nn.Parameter(torch.ones(dim))

    def _norm(self, x):
        return x * torch.rsqrt(x.pow(2).mean(-1, keepdim=True) + self.eps)

    def forward(self, x):
        output = self._norm(x.float()).type_as(x)
        return output * self.weight
    
if __name__ == "__main__":
    LayerNorm = RMSNorm(dim=4)
    hidden_state = torch.tensor([[[1, 2, 3, 4], [5, 6, 7, 8]]], dtype=torch.float32)
    middle = hidden_state.mean(-1, keepdim=True)
    print(middle)