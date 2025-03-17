#include "gemv.cuh"

/**
 * naive实现
 * 一个thread负责一个输出的计算
 */

void __global__ gemv_v1(const float* A, const float* B, float* C, int M, int N) {
    int row = blockDim.x * blockIdx.x + threadIdx.x;
    if (row < N) {
        float sum = 0;
        for (int i = 0; i < M; i++) {
            sum += A[i] * B[row * M + i];
        }
        C[row] = sum;
    }
}

void gemv_version1(const float* A, const float* B, float* C, int M, int N) {
    int block_size = 8;
    int grid_size = (N + block_size - 1) / block_size;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
        
    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemv_v1<<<grid_size, block_size>>>(A, B, C, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemv_v1: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}
