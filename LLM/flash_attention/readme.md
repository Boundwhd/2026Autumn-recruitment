## Flash Attention
FlashAttention旨在加速注意力计算并减少内存占用。FlashAttention利用底层硬件的内存层次知识，例如GPU的内存层次结构，来提高
计算速度和减少内存访问开销。 FlashAttention的核心原理是通过将输入分块并在每个块上执行注意力操作，从而减少对高带宽内存（HBM）的读写操作。

1. attention公式：
- $$attention = softmax(\frac{Q*K^T}{\sqrt{d_k}})V$$

2. softmax公式计算存在什么问题？

- 由于包涵幂指数计算，通常会导致数值溢出。
- 对于半精度fp16最大值在65536，当x=12时就溢出了。
- 工程中采用safe-softmax
$$safeSoftmax=\frac{e^{x_i-m}}{\Sigma_{j=1}^{N}{e^{x_j-m}}}$$

3. softmax可以流式计算降低访存复杂度

4. Flash attention中的所有计算使用加法结合律；做完softmax之后和V矩阵有个相乘累加

5. Flash attention中的tilling策略
    1. 矩阵分块：将大矩阵分成小块，处理矩阵时加载并处理一小部分，减少内存带宽压力

    2. Q,K,V 分解成小块，K,V在外循环，Q在内循环，减少全局内存访问

6. GQA和MQA采用index思想，而不是复制多份到显存中