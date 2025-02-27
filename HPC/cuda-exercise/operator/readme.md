## 1. Cuda线程模型
- Grid
- Block
- Thread
- Warp

## 2. 线程同步
__syncthreads()

## 3. Profile Kernel
- nvidia-smi or watch -n 0.1 nvidia-smi
- Nsight systems & compute
1. SM Utilization
2. Memory Throughput
3. Global Memory Access
4. L2 Cache Hit and Miss Rate
5. Active Warps 
6. Occupancy

- 缓存命中率：通常来讲，缓存的命中率越高则表示使用缓存的收益越高，应用的性能越好（响应时间越短、吞吐量越高），抗并发的能力越强。
- 命中：可以直接通过缓存获取到需要的数据。
- 不命中：无法直接通过缓存获取到想要的数据，需要再次查询数据库或者执行其它的操作。原因可能是由于缓存中根本不存在，或者缓存已经过期。

- **确保线程访问连续的内存地址，尽量减少每个线程之间的内存偏移。这样可以使得多个线程的内存请求合并为一个更高效的内存事务。**

## 4. 原子操作
原子操作确保某个线程对内存位置执行的操作在另一个线程可以访问或修改相同内存位置之前完全完成。这可以防止竞争条件（race conditions）。

由于在每次原子操作过程中我们限制了对单个内存位置的工作量，因此在速度上会稍微有所牺牲。原子操作在硬件上保证了内存安全，但代价是速度上的损失。

```cpp
锁定(memory_location)
old_value = *memory_location
*memory_location = old_value + increment
解锁(memory_location)
返回 old_value
```

## 5. Cuda stream流

## 6. API
1. cublas库
- 矩阵计算是列主序的维度问题
- cublasLt  cublasXt
2. cudnn
- 深度学习底层算子的加速实现
    1. 预编译单操作引擎
    2. 通用运行时融合引擎
    3. 专用运行时融合引擎
    4. 专用预编译融合引擎

## 7. 矩阵乘法的优化
1. 最简单实现
2. 全局内存共享
3. 共享内存实现

