#include "gemm.h"
#include <thread>
#include <vector>
template<const int BLOCK_SIZE>
void gemm_v4(const float* A, const float* B, float* C, int M, int K, int N, int lda, int ldb) {
    float As[BLOCK_SIZE * BLOCK_SIZE] = {0.0f};
    float Bs[BLOCK_SIZE * BLOCK_SIZE] = {0.0f};
    
    for (int i = 0; i < M; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            
            int k_cnt = 0;
            const float* new_A = A + (i * lda);
            const float* new_B = B + j;

            while(k_cnt < K) {

                for (int bi = 0; bi < BLOCK_SIZE; bi++) {
                    for (int bj = 0; bj < BLOCK_SIZE; bj++){
                        As[bi * BLOCK_SIZE + bj] = new_A[bi * lda + bj];
                        Bs[bi * BLOCK_SIZE + bj] = new_B[bi * ldb + bj];
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
                        C[(outi + i) * ldb + out + j] += sum[out];
                    }
                }
                k_cnt += BLOCK_SIZE;
                new_A += BLOCK_SIZE;
                new_B += BLOCK_SIZE * ldb;
            }
        }
    }
}

void gemm_cpu_version4(const float* A, const float* B, float* C, int M, int K, int N) {
    const int BLOCK_SIZE = 64;
    const int rows = 8;
    const int cols = 16;
    const int stride_A_row = M / rows;
    const int stride_B_col = N / cols;
    std::vector<std::thread> threadPool;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            threadPool.emplace_back(
                std::thread(
                    gemm_v4<BLOCK_SIZE>,
                    A + (i * stride_A_row * K), 
                    B + (j * stride_B_col),      
                    C + (i * stride_A_row * N) + (j * stride_B_col), 
                    stride_A_row, K, stride_B_col, K, N
                )
            );
        }
    }
    for (auto& t : threadPool) {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto GFLOPS = 4 / static_cast<float>(duration.count()) / (0.001f);

    std::ofstream outfile("kernel_timings.txt", std::ios::app);
    if (outfile.is_open()) {
        outfile << "gemm_cpu_v4:" << duration.count() <<
        " ms" << std::endl << GFLOPS << " GFLOP/s" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cout << "Fail to open file!" << std::endl;
    }
}