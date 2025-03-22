#include "gemm.h"
#include <thread>
#include <vector>
#include <immintrin.h>

void gemm_v7(const float* A, const float* B, float* C, int M, int K, int N, int lda, int ldb) {
    const uint bk = 32;
    const uint bm = 16;
    const uint bn = 16;
    float As[bm * bk] __attribute__((aligned(64))) = {0};
    float Bs[bk * bn] __attribute__((aligned(64))) = {0};

    // 遍历 C 矩阵中每一个块的初始位置
    for (int i = 0; i < M; i += bm) {
        for (int j = 0; j < N; j += bn) {

            int k_cnt = 0;
            const float* A_new = A + (i * lda);     //每一次计算时 A 块的初始位置
            const float* B_new = B + j;             //每一次计算时 B 块的初始位置
            float* C_new = C + (i * ldb) + j;

            while (k_cnt < K) {                     //每一次计算一个块，A B 矩阵需要移动 K/bk 次

                for (int ai = 0; ai < bm; ai++) {                   // A分块矩阵搬移
                    for (int aj = 0; aj < bk; aj++) {
                        As[ai * bk + aj] = A_new[ai * lda + aj];
                    }
                }

                for (int bi = 0; bi < bk; bi++) {                   // B分块矩阵搬移
                    for (int bj = 0; bj < bn; bj++) {
                        Bs[bi * bn + bj] = B_new[bi * ldb + bj];
                    }
                }
                
                for (int ci = 0; ci < bm; ci++) {
                    __m512 reg_tmp = _mm512_load_ps(C_new + (ci * ldb));
                    for (int ck = 0; ck < bk; ck++) {
                        float A_num = As[ci * bk + ck];
                        __m512 reg_A = _mm512_set1_ps(A_num);
                        __m512 reg_B = _mm512_load_ps(Bs + (ck * bn));
                        reg_tmp = _mm512_fmadd_ps(reg_A, reg_B, reg_tmp);
                    }
                    _mm512_store_ps((C_new + (ci * ldb)), reg_tmp);
                }

                k_cnt += bk;
                A_new += bk;
                B_new += bk * ldb;
            }
        }
    }
}

void gemm_cpu_version7(const float* A, const float* B, float* C, int M, int K, int N) {
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
                    gemm_v7,
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
        outfile << "gemm_cpu_v7:" << duration.count() <<
        " ms" << std::endl << GFLOPS << " GFLOP/s" << std::endl << std::endl;
        outfile.close();
    } else {
        std::cout << "Fail to open file!" << std::endl;
    }
}