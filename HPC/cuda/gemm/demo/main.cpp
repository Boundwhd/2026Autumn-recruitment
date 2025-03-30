#include <iostream>
#include <cuda_runtime_api.h>
#include <gemm.cuh>
using namespace std;

/**
 * GEMM VS Cublas
 * 向量大小：[2048, 2048]
 * 矩阵大小：[2048, 2048]
 * 输出大小：[2048, 2048]
*/

void test(float *out, int M, int N){
    for (int i = 0; i < M * N; i++) {
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
    const size_t K = 4096;
    const size_t N = 4096;

    float* A_h = (float*)malloc(M * K * sizeof(float));
    float* B_h = (float*)malloc(K * N * sizeof(float));
    float* C_h = (float*)malloc(M * N * sizeof(float));

    float* A_d;
    float* B_d;
    float* C_d;

    for (int i = 0; i < M * K; i++) {
        A_h[i] = 1.0f;
    }
    for (int i = 0; i < K * N; i++) {
        B_h[i] = 1.0f;
    }
    for (int i = 0; i < M * N; i++) {
        C_h[i] = 0.0f;
    }

    cudaMalloc((void**)&A_d, M * K * sizeof(float));
    cudaMalloc((void**)&B_d, K * N * sizeof(float));
    cudaMalloc((void**)&C_d, M * N * sizeof(float));
    
    cudaMemcpy(A_d, A_h, M * K * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(B_d, B_h, K * N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(C_d, C_h, M * N * sizeof(float), cudaMemcpyHostToDevice);
    
    std::ofstream outfile("kernel_timings.txt"); 
    if (outfile.is_open()) {
        outfile << "GEMM kernel contrast!" << endl << endl;
        outfile.close();
    }

    for (int i = 0; i < 1000; i++) {
        warm_up();
    }

    gemm_version1(A_d, B_d, C_d, M, K, N);
    cudaMemcpy(C_h, C_d, M * N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, M, N);

    gemm_version1pp(A_d, B_d, C_d, M, K, N);
    cudaMemcpy(C_h, C_d, M * N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, M, N);

    gemm_version2(A_d, B_d, C_d, M, K, N);
    cudaMemcpy(C_h, C_d, M * N * sizeof(float), cudaMemcpyDeviceToHost);
    test(C_h, M, N);

    // gemm_version3(A_d, B_d, C_d, M, K, N);
    // cudaMemcpy(C_h, C_d, M * N * sizeof(float), cudaMemcpyDeviceToHost);
    // test(C_h, M, N);

    // gemm_version4(A_d, B_d, C_d, M, K, N);
    // cudaMemcpy(C_h, C_d, M * N * sizeof(float), cudaMemcpyDeviceToHost);
    // test(C_h, M, N);
    return 0;
}