# 大模型训练
1. 精度：

降低所有浮点数的精度，数字、权重和激活所需的内存就会减少。
我们可以存储更多，更快地访问。

2. 带宽：

意味着极快的张量核心大部分时间都在等待，因为我们无法足够快的给他们提供数据。
硬件利用率达到60%，实际上做的非常好了已经。

## Tensor Core
- 张量核心是一个指令，做一些简单的矩阵乘法。
-   ```python
        torch.set_float32_matmul_precision('medium')
    ```
    我们要选择内部使用什么精度的数据做计算（输入和输出精度一致，内部会有裁剪）
- ```python
    with torch.autocast(device_type=device, dtype=torch.bfloat16):
  ```
  1. 除了权重变量，别的变量的type
  2. 有些层选择性的变成bf16


1. FP32 : S(1)  Range(8)  Precision(23)
2. TF32 : S(1)  Range(8)  Precision(10)
3. FP16 : S(1)  Range(5)  Precision(10)
4. BF16 : S(1)  Range(8)  Precision(7)

## torch.compile