#include "gemv.cuh"

void __global__ gemv_v4(const float* A, const float* B, float* C, int M, int N) {
    int warp_id = threadIdx.x / warpSize;
    int lane_id = threadIdx.x % warpSize;
    int row = (blockDim.x / warpSize) * blockIdx.x + warp_id;

    if (row < N) {
        float sum = 0;
        for (int i = lane_id; i < M; i += warpSize) {
            sum += A[i] * B[row * N + i];
        }

        for (int offset = 16; offset > 0; offset >>= 1) {
            sum += __shfl_down_sync(0xffffffff, sum, offset);
        }

        if (lane_id == 0) {
            C[row] = sum;
        }
    }
}

void gemv_version4(const float* A, const float* B, float* C, int M, int N) {
    int block_size = 1024;
    int grid_size = N;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
        
    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemv_v4<<<grid_size, block_size>>>(A, B, C, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemv_v4: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}