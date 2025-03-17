#include "gemv.cuh"

/**
 * 一个输出使用一个block计算
 * 每个block配置1024线程
 */


void __global__ gemv_v3(const float* A, const float* B, float* C, int M, int N) {
    int row = blockIdx.x;
    int col = threadIdx.x;

    __shared__ float mem[32];

    float sum = 0;
    for (int i = col; i < N; i += blockDim.x) {
        sum += A[i] * B[row * M + i];
    }

    for (int offset = 16; offset > 0; offset >>= 1) {
        sum += __shfl_down_sync(0XFFFFFFFF, sum, offset);
    }

    __syncthreads();

    int warptid = col % warpSize;
    int warpid = col / warpSize;
    if (warptid == 0) {
        mem[warpid] = warpid < (N / warpSize) ? sum : 0;
    }

    __syncthreads();

    if (warpid == 0) {
        sum = mem[warpid];
    }

    __syncthreads();

    for (int offset = 16; offset > 0; offset >>= 1) {
        sum += __shfl_down_sync(0XFFFFFFFF, sum, offset);
    }

    if (warpid == 0 && warpid == 0) {
        C[row] = sum;
    }
}


void gemv_version3(const float* A, const float* B, float* C, int M, int N) {
    int block_size = 1024;
    int grid_size = N;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
        
    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemv_v3<<<grid_size, block_size>>>(A, B, C, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemv_v3: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}