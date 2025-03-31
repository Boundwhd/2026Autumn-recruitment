#include "gemm.cuh"
template<const int BM, const int BN, const int BK, const int TM, const int TN>
__global__ void gemm_v5(float* A, float* B, float* C, int M, int K, int N) {
    const uint cRow = blockIdx.y;
    const uint cCol = blockIdx.x;
  
    const int threadCol = threadIdx.x % (BN / TN);
    const int threadRow = threadIdx.x / (BN / TN);
  
    __shared__ float As[BM * BK];
    __shared__ float Bs[BK * BN];
  
    A += cRow * BM * K;
    B += cCol * BN;
    C += cRow * BM * N + cCol * BN;
  
    const uint innerRowA = threadIdx.x / (BK / 4);
    const uint innerColA = threadIdx.x % (BK / 4);
    const uint innerRowB = threadIdx.x / (BN / 4);
    const uint innerColB = threadIdx.x % (BN / 4);

    float threadResults[TM * TN] = {0.0f};
    float regM[TM] = {0};
    float regN[TN] = {0};

    for (int bkIdx = 0; bkIdx < K; bkIdx += BK) {
        float4 tmp1 = reinterpret_cast<float4*>(&A[innerRowA * K + innerColA * 4])[0];
        float4 tmp2 = reinterpret_cast<float4*>(&A[(innerRowA + BM/2) * K + innerColA * 4])[0];
        
        As[(innerColA * 4 + 0) * BM + innerRowA] = tmp1.x;
        As[(innerColA * 4 + 1) * BM + innerRowA] = tmp1.y;
        As[(innerColA * 4 + 2) * BM + innerRowA] = tmp1.z;
        As[(innerColA * 4 + 3) * BM + innerRowA] = tmp1.w;

        As[(innerColA * 4 + 0) * BM + innerRowA + BM/2] = tmp2.x;
        As[(innerColA * 4 + 1) * BM + innerRowA + BM/2] = tmp2.y;
        As[(innerColA * 4 + 2) * BM + innerRowA + BM/2] = tmp2.z;
        As[(innerColA * 4 + 3) * BM + innerRowA + BM/2] = tmp2.w;

        reinterpret_cast<float4*>(&Bs[innerRowB * BN + innerColB * 4])[0] = 
            reinterpret_cast<float4*>(&B[innerRowB * N + innerColB * 4])[0];

        reinterpret_cast<float4*>(&Bs[(innerRowB + BK/2) * BN + innerColB * 4])[0] =
            reinterpret_cast<float4*>(&B[(innerRowB + BK/2) * N + innerColB * 4])[0];

        __syncthreads();

        A += BK;
        B += BK * N;

        for (uint dotIdx = 0; dotIdx < BK; dotIdx++) {
            for (int i = 0; i < TM; i++) {
                regM[i] = As[dotIdx * BM + (TM * threadRow + i)];
            }
            for (int j = 0; j < TN; j++) {
                regN[j] = Bs[dotIdx * BN + (TN * threadCol + j)];
            }
            for (int i = 0; i < TM; i++) {
                for (int j = 0; j < TN; j++) {
                    threadResults[i * TN + j] += regM[i] * regN[j];
                }
            }
        }
        __syncthreads();
    }

    for (int i = 0; i < TM; i++) {
        for (int j = 0; j < TN; j += 4) {
            float4 tmp = reinterpret_cast<float4*>(&C[(threadRow * TM + i) * N  + threadCol * TN + j])[0];
            tmp.x = threadResults[i * TN + j];
            tmp.y = threadResults[i * TN + j + 1];
            tmp.z = threadResults[i * TN + j + 2];
            tmp.w = threadResults[i * TN + j + 3];
            reinterpret_cast<float4 *>(&C[(threadRow * TM + i) * N + threadCol * TN + j])[0] = tmp;
        }
    }
}


void gemm_version5(float* A, float* B, float* C, int M, int K, int N) {
    const int BM = 64;
    const int BN = 64;
    const int BK = 8;
    const int TM = 8;
    const int TN = 8;

    dim3 gridDim(DIV_CEIL(N, BN), DIV_CEIL(M, BM));
    dim3 blockDim((BM * BN) / (TM * TN));

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    gemm_v5<BM, BN, BK, TM, TN><<<gridDim, blockDim>>>(A, B, C, M ,K ,N);
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);
    float GFLOPS_S = (2.0 * K * N * M) / milliseconds / 1e6;

    std::ofstream outfile("kernel_timings.txt", std::ios::app); 
    if (outfile.is_open()) {
        outfile << "gemm_v5: " << milliseconds << " ms" << std::endl << GFLOPS_S << "GFLOP/S" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }
    
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
}