#ifndef _GEMM_CUH_
#define _GEMM_CUH_
#include <cuda_runtime_api.h>
#include <iostream>
#include <fstream>
#define DIV_CEIL(a, b) (((a) + (b) - 1) / (b)) 

void warm_up();
void gemm_cublas(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_version1(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_version1pp(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_version2(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_version3(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_version4(const float* A, const float* B, float* C, int M, int K, int N);
void gemm_version5(float* A, float* B, float* C, int M, int K, int N);

#endif