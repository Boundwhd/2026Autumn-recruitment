# GEMV Kernel optimization

### Kernel 1: Naive Implementation
Each thread is responsible for computing one element of the output vector C.
This approach results in non-contiguous memory access by threads within a warp when accessing an (M*N) matrix, leading to performance degradation.

### Kernel 4: Warp Shuffle Gemv
Using one warp to compute one output result ensures that each warp accesses memory in a contiguous manner for row-major memory layout, thereby improving performance.



