#include "cuda_runtime.h"
#include <stdio.h>
#define N 1024
#define BLOCK_SIZE 32


__global__ void vector_sum(float *A, float *B, int size) {
    __shared__ float sm[32];
    
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int warpID = threadIdx.x / warpSize;
    int laneID = threadIdx.x % warpSize;

    float val = (idx < size) ? A[idx] : 0.0f;
    
    for (int offset = warpSize >> 1; offset > 0; offset >>= 1) {
        val += __shfl_down_sync(0xffffffff, val, offset);
    }

    if (laneID == 0) {
        sm[warpID] = val;
    }
    __syncthreads();

    if (warpID == 0) {
        int warpNum = blockDim.x / warpSize;
        val = (laneID < warpNum) ? sm[laneID] : 0;
        for (int offset = warpSize >> 1; offset > 0; offset >>= 1) {
            val += __shfl_down_sync(0xffffffff, val, offset);
        }
        if(laneID == 0) atomicAdd(B, val);
    }
}

int main() {
    // 初始化数据
    int size = N * sizeof(float);
    float *h_A = (float *)malloc(size);
    float *h_B = (float *)malloc(sizeof(float));  // 存储最终的求和结果
    h_B[0] = 0.0f;  // 初始化B为0

    // 填充输入向量A
    for (int i = 0; i < N; i++) {
        h_A[i] = 1.0f;  // 假设A的每个元素为1.0
    }

    // 分配设备内存
    float *d_A, *d_B;
    cudaMalloc((void **)&d_A, size);
    cudaMalloc((void **)&d_B, sizeof(float));

    // 将数据从主机拷贝到设备
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, sizeof(float), cudaMemcpyHostToDevice);

    // 计算所需的线程块数量
    int blockSize = BLOCK_SIZE;
    int gridSize = (N + blockSize - 1) / blockSize;

    // 调用CUDA内核
    vector_sum<<<gridSize, blockSize>>>(d_A, d_B, N);

    // 检查内核执行是否成功
    cudaDeviceSynchronize();

    // 将结果从设备复制回主机
    cudaMemcpy(h_B, d_B, sizeof(float), cudaMemcpyDeviceToHost);

    // 打印结果
    printf("The sum of the vector is: %f\n", h_B[0]);

    // 清理内存
    free(h_A);
    free(h_B);
    cudaFree(d_A);
    cudaFree(d_B);

    return 0;
}