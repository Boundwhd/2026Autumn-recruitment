# LLaMA3.1 架构解读

### 训练数据
- 预训练：
    - 大于15万亿token数据预训练
    - 数据混合包括常识，数学，推理，代码和任务
    - 多语言支持

- 微调：
    - 公开可用的指令数据集
    - 合成数据集微调，生产SFT示例来训练模型

### 模型架构
- Norm：RSMNorm 
- Self attention: GQA
- Embedding: ROPE
- FFN: SwiGLU

**注意力掩码 Attention Mask**：防止同一序列文档间出现自注意力，在标准预训练中效果有限，对长序列训练时非常重要。

**最大化达到 Scaling Law 算力数据比**：采用标准稠密Transformer架构，引入GQA，而非MOE，最大限度提高训练稳定性。


## Normalization
标准化技术主要是为了解决参数过大或过小以及其引发的梯度爆炸等问题。标准化技术通常会调整模型的输入或者是中间输入（层和层之间传递的值），调整方法通常是改变参数的分布（最常用的是将输入调整到均值为0，方差为1）。

常见的Norm手段包括Batch normalization，Layer normalization、Instance normalization、Group normalization。

- ### Layer Normalization
    它对每个样本的所有特征进行标准化，即计算该样本所有特征的均值和标准差，然后进行标准化。这样，每个样本的所有特征都会有相同的均值（0）和标准差（1），从而提升训练的稳定性。

- ### Root Mean Square Layer Normalization

    RMSNorm是对LayerNorm的一个改进，没有做re-center操作（移除了其中的均值项），可以看作LayerNorm在均值为0时的一个特例。论文通过实验证明，re-center操作不重要。

    RMSNorm 也是一种标准化方法，但与 LayerNorm 不同，它不是使用整个样本的均值和方差，而是使用平方根的均值来归一化，这样做可以降低噪声的影响。


## Self-attention

1. 为什么要除以根号dk: 
- 在自注意力机制中通过$\frac{1}{\sqrt{d_k}}$缩放点积为了防止点积随着$d_k$增大，点积随之变的很大。使用这个缩放点积因子使得缩放后数据的方差为1，使得点积保持在一个合理的范围内，确保后续softmax函数的有效工作。

2. softmax函数对数据的要求？
- #### 梯度消失的问题
    当输入的点积值非常大时，Softmax 会变得非常敏感，使得某个位置的概率几乎为 1，而其他位置的概率几乎为 0。这种情况下，Softmax 函数的梯度变得非常小，从而影响反向传播，导致梯度消失问题。因此，模型在训练时，权重更新会变得非常缓慢，导致训练变得不稳定。

3. softmax的作用是什么？
- 注意力分数 $q*k$ 本身没有直接的意义，softmax将他们转换为概率分布，形成有效的加权机制，以表示每个输入对输出的贡献程度，即注意力权重。 












### 参考文章
https://zhuanlan.zhihu.com/p/685181632

https://blog.csdn.net/qq_39970492/article/details/131125752