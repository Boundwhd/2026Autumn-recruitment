#include "gemm.cuh"

template<const int block_size>
void __global__ gemm_v1pp(const float* A, const float* B, float* C, int M, int K, int N){
    int row = (blockIdx.x * block_size) + (threadIdx.x / block_size);
    int col = (blockIdx.y * block_size) + (threadIdx.x % block_size);

    if (row < M && col < N) {
        float sum = 0.0;
        for (int i = 0; i < K; i++) {
            sum += A[row * K + i] * B[i * N + col];
        }
        C[row * N + col] = sum;
    }
}

void gemm_version1pp(const float* A, const float* B, float* C, int M, int K, int N) {
    dim3 block_size(32 * 32);
    dim3 grid_size(((M + 32 - 1) / 32), ((N + 32 - 1) / 32));

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    gemm_v1pp<32><<<grid_size, block_size>>>(A, B, C, M, K, N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    float GFLOPS_S = (2.0 * K * N * M) / milliseconds / 1e6;

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemm_v1pp: " << milliseconds << " ms" << std::endl << GFLOPS_S << "GFLOP/S" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}