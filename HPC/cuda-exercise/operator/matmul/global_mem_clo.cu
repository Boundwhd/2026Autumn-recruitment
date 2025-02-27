#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cublas_v2.h>
#include <cuda_runtime.h>

#define N 1024  
#define M 1024  
#define K 1024  

template<const int BLOCKSIZE>
__global__ void global_mem_clo(float *A, float *B, float *C, int m, int n, int k){
    const uint cRow = blockidx.x * BLOCKSIZE + (threadIdx.x / BLOCKSIZE);
    const uint cCol = blockIdx.y * BLOCKSIZE + (threadIdx.x % BLOCKSIZE);

    if (cRow < m && cCol < n) {
        float sum = 0.0f;
        for (int l = 0; l < k; l++) {
            sum += A[cRow * k + l] * B[l * N + cCol];
        }
        c[cRow * N + cCol] = sum;
    }
}