#include <iostream>
#include <cuda_runtime_api.h>
#include "gemv.cuh"
using namespace std;

/**
 * GEMV VS Cublas
 * 向量大小：[1, 4096]
 * 矩阵大小：[4096, 4096]
 * 输出大小：[1, 4096]
*/

void test(float *out, int N){
    for (int i = 0; i < N; i++) {
        if (out[i] != 4096) {
            cout << "Error!" << endl;
            return;
        }
    }
    cout << "pass successfully!" << endl;
    return;
}


int main() {
    const size_t M = 4096;
    const size_t N = 4096;

    float* A_h = (float*)malloc(M * sizeof(float));
    float* B_h = (float*)malloc(M * N * sizeof(float));
    float* C_h = (float*)malloc(N * sizeof(float));

    float* A_d;
    float* B_d;
    float* C_d;

    for (int i = 0; i < M; i++) {
        A_h[i] = 1.0f;
    }
    for (int i = 0; i < M * N; i++) {
        B_h[i] = 1.0f;
    }
    for (int i = 0; i < N; i++) {
        C_h[i] = 0.0f;
    }

    cudaMalloc((void**)&A_d, M * sizeof(float));
    cudaMalloc((void**)&B_d, M * N * sizeof(float));
    cudaMalloc((void**)&C_d, N * sizeof(float));
    
    cudaMemcpy(A_d, A_h, M * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(B_d, B_h, M * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(C_d, C_h, N * sizeof(float), cudaMemcpyHostToDevice);
    
    std::ofstream outfile("kernel_timings.txt"); 
    if (outfile.is_open()) {
        outfile << "GEMV kernel contrast!" << endl << endl;
        outfile.close();
    }
    
    for (int i = 0; i < 1000; i++) {
        warm_up();
    }

    gemv_cublas(A_d, B_d, C_d, M, N);
    cudaMemcpy(C_h, C_d, N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, N);

    gemv_version1(A_d, B_d, C_d, M, N);
    cudaMemcpy(C_h, C_d, N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, N);

    gemv_version2(A_d, B_d, C_d, M, N);
    cudaMemcpy(C_h, C_d, N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, N);

    gemv_version3(A_d, B_d, C_d, M, N);
    cudaMemcpy(C_h, C_d, N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, N);

    gemv_version4(A_d, B_d, C_d, M, N);
    cudaMemcpy(C_h, C_d, N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, N);

    return 0;
}
