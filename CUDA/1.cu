#include <stdio.h>
#include <stdlib.h>
#include <math.h>

__global__ void vecAdd(double *a, double *b, double *c, int n) {
	int id = blockIdx.x*blockDim.x + threadIdx.x;
	if (id < n) c[id] = a[id] + b[id];
}

int main(int argc, char** argv) {
	int n = 100;
	double *ha, *hb, *hc, *da, *db, *dc;
	size_t bytes = n*sizeof(double);
	ha = (double*)malloc(bytes);
	hb = (double*)malloc(bytes);
	hc = (double*)malloc(bytes);
	cudaMalloc(&da, bytes);
	cudaMalloc(&db, bytes);
	cudaMalloc(&dc, bytes);
	int i;
	for(i = 0; i < n; i++)
		ha[i] = hb[i] = i;
	cudaMemcpy(da, ha, bytes, cudaMemcpyHostToDevice);
	cudaMemcpy(db, hb, bytes, cudaMemcpyHostToDevice);
	int blockSize, gridSize;
	blockSize = 1024;
	gridSize = (int)ceil((float)n/blockSize);
	vecAdd<<<gridSize, blockSize>>>(da, db, dc, n);
	cudaMemcpy(hc, dc, bytes, cudaMemcpyDeviceToHost);
	for(i = 0; i < n; i++)
		printf("\n%f + %f = %f\n",ha[i], hb[i], hc[i]);
	cudaFree(da);
	cudaFree(db);
	cudaFree(dc);
	free(ha);
	free(hb);
	free(hc);
	return 0;
}
