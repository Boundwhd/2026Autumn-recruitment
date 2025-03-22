#include "gemm.h"
#include <cstring>
#define M 2048
#define N 1024
#define K 1024

/**
 * GEMM VS 
 * 向量大小：[2048, 1024]
 * 矩阵大小：[1024, 1024]
 * 输出大小：[2048, 1024]
*/

int main() {
    const size_t size_A = M * K * sizeof(float);
    const size_t size_B = K * N * sizeof(float);
    const size_t size_C = M * N * sizeof(float);

    float* A_h = (float*)std::aligned_alloc(64, size_A);
    float* B_h = (float*)std::aligned_alloc(64, size_B);
    float* C_h = (float*)std::aligned_alloc(64, size_C);

    for (int i = 0; i < M * K; i++) {
        A_h[i] = 1.0f;
    }
    for (int i = 0; i < K * N; i++) {
        B_h[i] = 1.0f;
    }
    for (int i = 0; i < M * N; i++) {
        C_h[i] = 0.0f;
    }

    std::ofstream outfile("kernel_timings.txt"); 
    if (outfile.is_open()) {
        outfile << "GEMM kernel contrast!" << std::endl << std::endl;
        outfile.close();
    }
    for (int i = 0; i < 100; i++) {
        warm_up();
    }
    
    gemm_cpu_OpenBLAS(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version1(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version2(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version3(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version4(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version5(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version6(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);

    memset(C_h, 0, size_C);
    gemm_cpu_version7(A_h, B_h, C_h, M, K, N);
    test(C_h, M, N);
    return 0;
}