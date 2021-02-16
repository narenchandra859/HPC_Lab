#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define BLOCK_SIZE 3

int w = 6, h = 6;
int size = w*h;
int memSize = sizeof(float)*size;

__global__ void matrixMul(float *a, float *b, float *c, int w, int h) {
  int tx = (blockIdx.x*blockDim.x)+threadIdx.x;
  int ty = (blockIdx.y*blockDim.y)+threadIdx.y;
  float v = 0;
  int i;
  for(i = 0; i < w; i++)
    v += a[ty * w + i] * b[i * h + tx];
  c[ty * w + tx] = v;
}

void printMat(float *arr) {
  int i;
  for(i=0;i<size;i++) {
    printf("%f ", arr[i]);
    if((i+1)%w==0) printf("\n");
  }
}

int main(int argc, char** argv) {
  float *ha, *hb, *hc;
  int i;
  ha = (float*)malloc(memSize);
  hb = (float*)malloc(memSize);
  hc = (float*)malloc(memSize);
  for(i=0; i<size; i++)
    ha[i] = hb[i] = i;
  printf("\nMatrix A:\n");
  printMat(ha);
  printf("\nMatrix B:\n");
  printMat(hb);
  float *da, *db, *dc;
  cudaMalloc(&da, memSize);
  cudaMalloc(&db, memSize);
  cudaMalloc(&dc, memSize);
  cudaMemcpy(da, ha, memSize, cudaMemcpyHostToDevice);
  cudaMemcpy(db, hb, memSize, cudaMemcpyHostToDevice);
  dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
  dim3 grid(w/threads.x, h/threads.y);
  matrixMul<<<grid, threads>>>(da, db, dc, w, w);
  cudaMemcpy(hc, dc, memSize, cudaMemcpyDeviceToHost);
  printf("\nMatrix C:\n");
  printMat(hc);
  cudaFree(da);cudaFree(db);cudaFree(dc);
  free(ha);free(hb);free(hc);
  return 0;
}
