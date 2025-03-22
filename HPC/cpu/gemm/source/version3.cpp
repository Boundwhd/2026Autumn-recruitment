#include "gemm.h"

template<const int BLOCK_SIZE>
void gemm_v3(const float* A, const float* B, float* C, int M, int K, int N) {
    float As[BLOCK_SIZE * BLOCK_SIZE] = {0.0f};
    float Bs[BLOCK_SIZE * BLOCK_SIZE] = {0.0f};
    
    for (int i = 0; i < M; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            
            int k_cnt = 0;
            const float* new_A = A + (i * K);
            const float* new_B = B + j;

            while(k_cnt < K) {

                for (int bi = 0; bi < BLOCK_SIZE; bi++) {
                    for (int bj = 0; bj < BLOCK_SIZE; bj++){
                        As[bi * BLOCK_SIZE + bj] = new_A[bi * K + bj];
                        Bs[bi * BLOCK_SIZE + bj] = new_B[bi * N + bj];
                    }
                }
    
                for (int outi = 0; outi < BLOCK_SIZE; outi++) {
                    float sum[BLOCK_SIZE] = {0};
                    for (int outk = 0; outk < BLOCK_SIZE; outk++) {
                        for (int outj = 0; outj < BLOCK_SIZE; outj++) {
                            sum[outj] += 
                                As[outi * BLOCK_SIZE + outk] * Bs[outk * BLOCK_SIZE + outj];
                        }
                    }
                    for (int out = 0; out < BLOCK_SIZE; out++) {
                        C[(outi + i) * N + out + j] += sum[out];
                    }
                }
                k_cnt += BLOCK_SIZE;
                new_A += BLOCK_SIZE;
                new_B += BLOCK_SIZE * N;
            }
        }
    }
}



void gemm_cpu_version3(const float* A, const float* B, float* C, int M, int K, int N) {
    const int block_size = 32;
    auto start = std::chrono::high_resolution_clock::now();
    gemm_v3<block_size>(A, B, C, M, K, N);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    auto GFLOPS = 4 / static_cast<float>(duration.count()) / (0.001f);

    std::ofstream outfile("kernel_timings.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "gemm_cpu_v3:" << duration.count() <<
        " ms" << std::endl << GFLOPS << " GFLOP/s" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cout << "Fail to open file!" << std::endl;
    }
}