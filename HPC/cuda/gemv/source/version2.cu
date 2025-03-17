#include "gemv.cuh"
/**
 * 采取float4向量化指令，减少指令数据
 * 在小数据规模上无太大提升
 * 优化的是Icache，提高其访存命中
 */
void __global__ gemv_v2(const float* A, const float* B, float* C, int M, int N) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    float4* A_4 = reinterpret_cast<float4*>(const_cast<float*>(A));
    float4* B_4 = reinterpret_cast<float4*>(const_cast<float*>(B));
    if (row < N) {
        float sum = 0;
        int M_4 = M / 4;
        for (int i = 0; i < M / 4; i++) {
            sum += A_4[i].x * B_4[row * M_4 + i].x;
            sum += A_4[i].y * B_4[row * M_4 + i].y;
            sum += A_4[i].z * B_4[row * M_4 + i].z;
            sum += A_4[i].w * B_4[row * M_4 + i].w;
        }
        
        for (int i = M_4 * 4; i < M; i++) {
            sum += A[i] * B[row * M + i];
        }

        C[row] = sum;
    }
}

void gemv_version2(const float* A, const float* B, float* C, int M, int N) {
    int block_size = 32;
    int grid_size = (N + block_size - 1) / block_size;

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemv_v2<<<grid_size, block_size>>>(A, B, C, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "gemv_v2: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}