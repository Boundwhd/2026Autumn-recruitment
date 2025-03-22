#include <cblas.h>
#include "gemm.h"

void gemm_cpu_OpenBLAS(const float* A, const float* B, float* C, int M, int K, int N) {
    auto start = std::chrono::high_resolution_clock::now();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
        M, N, K, 1.0, A, K, B, N, 0.0, C, N);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto GFLOPS = 4 / static_cast<float>(duration.count()) / (0.001f);
    std::ofstream outfile("kernel_timings.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "gemm_cpu_OpenBLAS:" << duration.count() <<
        " ms" << std::endl << GFLOPS << " GFLOP/s" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cout << "Fail to open file!" << std::endl;
    }
}