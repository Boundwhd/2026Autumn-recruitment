#include "gemv.cuh"
__global__ void warmup_kernel() {

}

void warm_up() {
    warmup_kernel<<<32, 32>>>();
    cudaDeviceSynchronize(); 

    int *d_temp;
    cudaMalloc((void**)&d_temp, sizeof(int));
    cudaFree(d_temp);
}