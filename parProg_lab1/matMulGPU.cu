__global__ void matmul1(float* a, float* b, int n, float* c)
{
    float sum = 0.0f;

    int ia = (blockDim.y * blockIdx.y + threadIdx.y) * n;
    int ib = blockDim.x * blockIdx.x + threadIdx.x;
    int ic = ia + ib;

    for (int k = 0; k < n; k++)
        sum += a[ia + k] * b[ib + k * n];

    c[ic] = sum;
}

#define kernel matmul1
#include "mainGPU.h"