#include "gemm.cuh"

template<const int BLOCK_SIZE>
void __global__ gemm_v2(const float* A, const float* B, float* C, int M, int K, int N) {
    int crow = blockIdx.y;
    int ccol = blockIdx.x;

    int row_thread = threadIdx.x / BLOCK_SIZE;
    int col_thread = threadIdx.x % BLOCK_SIZE;

    A += crow * BLOCK_SIZE * K;
    B += ccol * BLOCK_SIZE;
    C += crow * BLOCK_SIZE * N + ccol * BLOCK_SIZE;

    __shared__ float AS[BLOCK_SIZE * BLOCK_SIZE];
    __shared__ float BS[BLOCK_SIZE * BLOCK_SIZE];

    float sum = 0.0;
    for (int bkidx = 0; bkidx < K; bkidx += BLOCK_SIZE) {
        AS[row_thread * BLOCK_SIZE + col_thread] = A[row_thread * K + col_thread];
        BS[row_thread * BLOCK_SIZE + col_thread] = B[row_thread * N + col_thread];

        __syncthreads();

        A += BLOCK_SIZE;
        B += BLOCK_SIZE * N;

        for (int i = 0; i < BLOCK_SIZE; i++) {
            sum += AS[row_thread * BLOCK_SIZE + i] * BS[i * BLOCK_SIZE + col_thread];
        }
        
        __syncthreads();
    }

    C[row_thread * N + col_thread] = sum;
}


void gemm_version2(const float* A, const float* B, float* C, int M, int K, int N) {
    const int BLOCK_SIZE = 32;
    int block_size = 1024;
    dim3 grid_size((N + BLOCK_SIZE - 1) / BLOCK_SIZE, (M + BLOCK_SIZE - 1) / BLOCK_SIZE);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemm_v2<BLOCK_SIZE><<<grid_size, block_size>>>(A, B, C, M, K, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemm_v2: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}