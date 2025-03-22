#include "gemm.h"

void gemm_v2(const float* A, const float* B, float* C, int M, int K, int N) {
    for (int i = 0; i < M; i++) {
        float sum[N] = {0};
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < N; j++) {
                sum[j] += A[i * K + k] * B[k * N + j];
            }
        }
        for (int out = 0; out < N; out++) {
            C[i * N + out] = sum[out];
        }
    }
}

void gemm_cpu_version2(const float* A, const float* B, float* C, int M, int K, int N) {
    auto start = std::chrono::high_resolution_clock::now();
    gemm_v2(A, B, C, M, K, N);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    auto GFLOPS = 4 / static_cast<float>(duration.count()) / (0.001f);

    std::ofstream outfile("kernel_timings.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "gemm_cpu_v2:" << duration.count() <<
        " ms" << std::endl << GFLOPS << " GFLOP/s" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cout << "Fail to open file!" << std::endl;
    }
}