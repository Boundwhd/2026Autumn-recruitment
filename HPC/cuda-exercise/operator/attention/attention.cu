#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>

void cudaCheck(cudaError_t error, const char* file, int line) {
    if (error != cudaSuccess) {
        printf("[CUDA ERROR] at file %s:%d:\n%s\n", file, line, cudaGetErrorString(error));
        exit(EXIT_FAILURE);
    }
}

void init_matrix(float* add, size_t size, int value) {
    for (size_t i = 0; i < size; i++) {
        add[i] = value;
    }
}

// input (B, T, 3C)
// preatt att are (B, NH, T, T)
// output (B, T, C)
template<const int BLOCKSIZE>

__global__ void attention_query_key_kernel1(float* preatt, const float* inp, int B, int T, int C, int NH) {
    int idx = blockIdx.x * blockDim.x + threadIdx;
    int total_threads = B * NH * T * T;

    if (idx < total_threads) {
        int t2 = idx % T;
        int t = (idx / T) % T;
        if (t2 > t) {
            preatt[idx] = -INFINITY;
            return;
        }
        int h = (idx / (T * T)) % NH;
        int b = idx / (NH * T * T);







    }
}

int main() {
    int B = 2;      // Btach-size
    int H = 8;      // Multi-Attention Head
    int T = 512;    // Q,K,V 矩阵行数量
    int C = 1024;   // Q,K,V 矩阵列数量

    float *h_in;
    float *d_in;
    float *d_out;
    float *out_cpu, *out_cuda;

    // 主机分配内存
    h_in = (float*)malloc(B * T * 3*C * sizeof(float));
    // Cuda分配内存
    cudaMalloc((void**)&d_in, B * H * T * T * sizeof(float));

    int total_threads = B * H * T * T;
    int block_size = 1024;
    int grid_size = (total_threads + block_size - 1) / block_size; 

    
}