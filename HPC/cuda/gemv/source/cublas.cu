#include <cublas_v2.h>
#include <gemv.cuh>

void gemv_cublas(const float* A, const float* B, float* C, int M, int N) {
    cublasHandle_t handle;
    cublasCreate(&handle);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    float alpha = 1.0f;
    float beta = 0.0f;

    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        cublasSgemv(handle, CUBLAS_OP_N, N, M, &alpha, B, M, A, 1, &beta, C, 1);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemv_cublas: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    cublasDestroy(handle);
}