#ifndef _GEMM_H_
#define _GEMM_H_
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>

inline void test(float *out, int M, int N){
    for (int i = 0; i < M * N; i++) {
        if (out[i] != 1024) {
            std::cout << "Error!" << std::endl;
            return;
        }
    }
    std::cout << "pass successfully!" << std::endl;
    return;
}

inline void warm_up() {
    std::vector<int> a(1000, 1);
    std::vector<int> b(1000, 1);
    int d = 0;
    for (int i = 0; i < 1000; i++) {
        int c = (a[i] * b[i]) + d;
    }
}

void gemm_cpu_OpenBLAS(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version1(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version2(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version3(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version4(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version5(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version6(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_cpu_version7(const float* A, const float* B, float* C, int M, int K, int N);
#endif