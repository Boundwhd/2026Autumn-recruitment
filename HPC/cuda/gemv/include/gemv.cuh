#ifndef _GEMV_CUH_
#define _GEMV_CUH_
#include <cuda_runtime_api.h>
#include <iostream>
#include <fstream>
#define COUNT 1


void warm_up();
void gemv_cublas(const float* A, const float* B, float* C, int M, int N);
void gemv_version1(const float* A, const float* B, float* C, int M, int N);
void gemv_version2(const float* A, const float* B, float* C, int M, int N);
void gemv_version3(const float* A, const float* B, float* C, int M, int N);
void gemv_version4(const float* A, const float* B, float* C, int M, int N);

#endif