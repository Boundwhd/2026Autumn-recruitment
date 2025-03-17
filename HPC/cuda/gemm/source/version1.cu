#include "gemm.cuh"

void __global__ gemm_v1(const float* A, const float* B, float* C, int M, int K, int N){
    int row = blockDim.y * blockIdx.y + threadIdx.y;
    int col = blockDim.x * blockIdx.x + threadIdx.x;

    if (row < M && col < N) {
        float sum = 0.0;
        for (int i = 0; i < K; i++) {
            sum += A[row * K + i] * B[i * N + col];
        }
        C[row * N + col] = sum;
    }
}

void gemm_version1(const float* A, const float* B, float* C, int M, int K, int N) {
    dim3 block_size(32, 32);
    dim3 grid_size(((N + 32 - 1) / 32), ((M + 32 - 1) / 32));

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemm_v1<<<grid_size, block_size>>>(A, B, C, M, K, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemm_v1: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}