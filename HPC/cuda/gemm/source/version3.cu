#include "gemm.cuh"

template <const int BM, const int BN, const int BK, const int TM>
void __global__ gemm_v3(const float* A, const float* B, float* C, int M, int K, int N) {
    const uint cRow = blockIdx.y;
    const uint cCol = blockIdx.x;

    int threadRow = threadIdx.x / BN;
    int threadCol = threadIdx.x % BN;

    __shared__ float As[BM * BK];
    __shared__ float Bs[BK * BN];

    A += cRow * K * BM;
    B += cCol * BN;
    C += cRow * K * BM + cCol * BN;


    const uint innerRowA = threadIdx.x / BK;
    const uint innerColA = threadIdx.x % BK;
    const uint innerRowB = threadIdx.x / BN;
    const uint innerColB = threadIdx.x % BN;

    float threadResult[TM] = {0.0};

    for (int bkidx = 0; bkidx < K; bkidx += BK) {
        As[innerRowA * BK + innerColA] = A[innerRowA * K + innerColA];
        Bs[innerRowB * BN + innerColB] = B[innerRowB * N + innerColB];

        __syncthreads();

        A += BK;
        B += N * BK;

        for (int i = 0; i < BK; i++) {
            float tmp_B = Bs[i * BN + threadCol];
            for (int j = 0; j < TM; j++) {
                threadResult[j] += As[(threadRow * TM + j) * BK + i] * tmp_B;
            }
        }
        __syncthreads();
    }

    for (int i = 0; i < TM; i++) {
        C[(threadRow * TM + i) * N + threadCol] = threadResult[i]; 
    }
}

void gemm_version3(const float* A, const float* B, float* C, int M, int K, int N) {
    const int BM = 64;
    const int BN = 64;
    const int BK = 8;
    const int TM = 8;
    dim3 gridDim(((N + BN - 1) / BN), ((M + BM - 1) / BM));
    dim3 blockDim((BM * BN) / TM);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    for (int i = 0; i < COUNT; i++) {
        gemm_v3<BM, BN, BK, TM><<<gridDim, blockDim>>>(A, B, C, M ,K ,N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemm_v3: " << milliseconds << " ms" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}