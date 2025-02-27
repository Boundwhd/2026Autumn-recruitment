#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cublas_v2.h>
#include <cuda_runtime.h>

#define N 1024  // A和C的行数
#define M 1024  // B的列数
#define K 1024  // A和B的列数（A的列数等于B的行数）

template<const int BLOCKSIZE>
__global__ void shared_mem_sgemm(float *A, float *B, float *C, int m, int n, int k) {
    const uint cROW = blockIdx.x;
    const uint cCol = blockIdx.y;

    __shared__ float AS[BLOCKSIZE * BLOCKSIZE];
    __shared__ float BS[BLOCKSIZE * BLOCKSIZE];

    const uint threadCol = threadIdx.x % BLOCKSIZE;
    const uint threadRow = threadIdx.x / BLOCKSIZE;

    A += cROW * K * BLOCKSIZE;
    B += cCol * BLOCKSIZE;
    C += cROW * N * BLOCKSIZE + cCol * BLOCKSIZE;

    float temp = 0.0f;
    for (int bkidx = 0; bkidx < k; bkidx += BLOCKSIZE) {
        AS[threadRow * BLOCKSIZE + threadCol] = A[threadRow * K + threadCol];
        BS[threadRow * BLOCKSIZE + threadCol] = B[threadRow * N + threadCol];
        __syncthreads();

        A += BLOCKSIZE;
        B += BLOCKSIZE * n;

        for (int dotidx = 0; dotidx < BLOCKSIZE; dotidx++) {
            temp += AS[threadRow * BLOCKSIZE + dotidx] * BS[dotidx * BLOCKSIZE + threadCol];
        }

        __syncthreads();
    }
    C[threadRow * N + threadCol] = temp;
}

// CUDA主函数，调用shared_mem_sgemm内核
int main() {
    // 定义矩阵的大小
    int sizeA = M * K * sizeof(float);  // A矩阵的大小
    int sizeB = K * N * sizeof(float);  // B矩阵的大小
    int sizeC = M * N * sizeof(float);  // C矩阵的大小

    // 分配主机内存
    float *h_A = (float *)malloc(sizeA);
    float *h_B = (float *)malloc(sizeB);
    float *h_C = (float *)malloc(sizeC);

    // 初始化矩阵A和B
    for (int i = 0; i < M * K; i++) {
        h_A[i] = 1.0f;  // 设置A矩阵的每个元素为1.0
    }
    for (int i = 0; i < K * N; i++) {
        h_B[i] = 1.0f;  // 设置B矩阵的每个元素为1.0
    }

    // 分配设备内存
    float *d_A, *d_B, *d_C;
    cudaMalloc((void **)&d_A, sizeA);
    cudaMalloc((void **)&d_B, sizeB);
    cudaMalloc((void **)&d_C, sizeC);

    // 将数据从主机拷贝到设备
    cudaMemcpy(d_A, h_A, sizeA, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, sizeB, cudaMemcpyHostToDevice);
    cudaMemcpy(d_C, h_C, sizeC, cudaMemcpyHostToDevice);

    // 定义线程块和网格的大小
    const int BLOCKSIZE = 32;  // 假设每个块有16x16线程
    dim3 threadsPerBlock(32 * 32);
    dim3 numBlocks((M + BLOCKSIZE - 1) / BLOCKSIZE, (N + BLOCKSIZE - 1) / BLOCKSIZE);

    // 启动CUDA内核
    shared_mem_sgemm<BLOCKSIZE><<<numBlocks, threadsPerBlock>>>(d_A, d_B, d_C, M, N, K);

    // 检查内核执行是否成功
    cudaDeviceSynchronize();

    // 从设备拷贝结果到主机
    cudaMemcpy(h_C, d_C, sizeC, cudaMemcpyDeviceToHost);

    // 打印部分结果（这里只打印第一个元素）
    printf("C[0][0] = %f\n", h_C[0]);

    // 清理内存
    free(h_A);
    free(h_B);
    free(h_C);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
