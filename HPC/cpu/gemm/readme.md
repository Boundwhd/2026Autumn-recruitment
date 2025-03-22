<font face="Caslon">

## The Art and Science of Matrix Multiplication — A Journey from Basics to Optimization Mastery

In this post, I’ll iteratively optimize an implementation of matrix multiplication written in *CPP* running on CPU. Embarking on a performance optimization journey, I will take the General Matrix Multiplication (GEMM) operator from the OpenBLAS library as my starting point. 

Through a step-by-step optimization strategy, combined with various high-performance techniques, I aim to gradually break through performance bottlenecks, ultimately pushing the operator's computational efficiency to rival—and in some scenarios, surpass—that of OpenBLAS.

### Environment Setup
We use the matrix multiplication of ​**A[2048, 1024] * B[1024, 1024]** to obtain the resulting matrix ​**C[2048, 1024]** as our experimental workload. The CPU used in this experiment is the ​**AMD Ryzen Threadripper 7960X**, a high-performance 24-core processor designed for compute-intensive tasks. The total floating-point operations (FLOPs) for this computation are approximately:

$$ \text{FLOPs} = 2 \times 2048 \times 1024 \times 1024 \approx 4\text{GFLOPS}$$

| Kernel                     | GFLOP/s   | Kernel Time (ms) |Performance Relative to OpenBLAS |
|----------------------------|-----------|------------------|---------------------------------|
| Naive Implementation       | 0.5       | 8339             | 0.3%                            |
| Contiguous Access Memory   | 0.7       | 5471             | 0.4%                            |      
| Tilling                    | 0.9       | 4868             | 0.5%                            |
| Multi Threads              | 16.6      | 383              | 10.0%                           |
| SIMD                       | 33.6      | 119              | 20.2%                           |
| SIMD (Memory Alignment)    | 38.1      | 105              | 22.9%                           |
| Compiler Optimization      | 85.1      | 47               | 51.0%                           |
| OpenBLAS (Baseline)        | 166.7     | 24               | 100.0%                          |

### 1. Naive Implementation  
The most fundamental matrix multiplication implementation comprises three nested loops. The outermost loop iterates over the rows of matrix A and the corresponding row indices of matrix C. The middle loop traverses the columns of matrix B and the corresponding column indices of matrix C. The innermost loop performs the dot product calculation by iterating through all K corresponding element pairs. 

Upon exiting the innermost loop, a single element in matrix C is fully computed. Subsequent termination of the middle loop signifies the completion of an entire row in matrix C. Ultimately, when all outer loops complete execution, the entire matrix multiplication operation is finalized (understanding these three points is crucial for subsequent optimization efforts, as it clearly reveals the hierarchical structure of the computation process and identifies potential performance bottlenecks).

The current matrix multiplication kernel requires approximately 8 seconds of execution time, delivering a computational efficiency of 0.5 GFLOPS/s. This achieves only 0.3% of the performance benchmark set by the OpenBLAS library. We will systematically optimize this operator through targeted improvements to fully unlock its hardware potential.
### 2. Contiguous Access Memory
<font face="Segoe Print">

##### Cache Hit
When a processor attempts to access data, it first queries the CPU's cache hierarchy. If the requested data resides in any cache level (L1/L2/L3), this constitutes a **​cache hit**. However, if the data isn’t in the cache, the computer has to go all the way to the main memory to fetch it, which is much slower. This is known as a **​cache miss**. We always want to maximize cache hits and minimize cache misses to keep things running smoothly and efficiently.

##### The Cache Mechanism
Modern CPUs employ fixed-size cache lines (typically 64 bytes) as the fundamental unit for data transfer. When accessing a float at memory address 0x00, the processor loads the entire 64-byte cache line spanning addresses 0x00 to 0x3F. This design leverages the principle of spatial locality, enabling subsequent accesses to adjacent addresses like 0x04 and 0x08 to achieve direct cache hits, thereby dramatically reducing memory latency.</font>

Let's review the previous kernel, the access pattern for matrix A aligns well with cache optimization principles: it accesses elements sequentially row by row, fully leveraging the spatial locality of cache lines. However, the access pattern for matrix B creates a significant performance bottleneck. Since the matrix is stored in row-major order, each access spans a stride of N elements. This strided access pattern disrupts spatial locality, drastically reducing cache hit rates and making it the primary performance bottleneck in the computation process.

To optimize cache utilization for matrix B, we can simply reorder the nested loops (swapping the positions of the k and j loops). This modification ensures that matrix K (or B) is accessed sequentially in memory, aligning with cache-friendly access patterns. Empirical data shows that this adjustment indeed yields performance improvements, demonstrating the value of cache-aware programming. However, the gains are modest, suggesting additional bottlenecks may dominate the computation.

### 3. Tilling 
Main memory access is very slow, so we want to store matrix data in the cache to speed things up. However, modern CPU caches are small (usually 256KB to 6MB), making it impossible to fit entire matrices. This limitation leads us to use ​matrix blocking (tile-based optimization) — a method that divides matrices into smaller, cache-friendly sub-blocks.

When computing elements of matrix ​C, the algorithm strategically caches corresponding row blocks from ​A and column blocks from ​B in CPU registers or cache memory. For each block pair, partial products are calculated and temporarily stored in their respective positions within ​C. As the algorithm iterates through subsequent blocks by sliding ​A and ​B across the matrix, these intermediate values accumulate progressively in ​C, ensuring that each element’s final value reflects the cumulative sum of all relevant block contributions.

When computing the blocked matrix operations, we retain the optimization techniques introduced in **​Kernel 2**. Although the performance improvement after matrix blocking is marginal, the experimental results confirm the validity of our theoretical approach. In the next phase, we will adopt more aggressive optimization strategies to further enhance performance.

### 4. Multi Threads

### 5. SIMD

### 6. SIMD (Memory Alignment)

### 7. Compiler Optimization


</font>