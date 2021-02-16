#include <stdio.h>
#include <stdlib.h>

__global__ void vecAdd(double *a, double *b, double *c, int n) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	c[idx] = a[idx] + b[idx];
}

int main(int argc, char** argv) {
	double *ha, *hb, *hc;
	double *da, *db, *dc;
	int i, n = 100;
	size_t memsize = sizeof(double)*n;
	ha = (double *)malloc(memsize);
	hb = (double *)malloc(memsize);
	hc = (double *)malloc(memsize);
	for(i = 0; i < n; i++) {
		ha[i] = rand() % 10000;
		hb[i] = rand() % 10000;
	}
	cudaMalloc(&da, memsize);
	cudaMalloc(&db, memsize);
	cudaMalloc(&dc, memsize);
	cudaMemcpy(da, ha, memsize, cudaMemcpyHostToDevice);
	cudaMemcpy(db, hb, memsize, cudaMemcpyHostToDevice);
	vecAdd<<<n/10, 10>>>(da, db, dc, n);
	cudaMemcpy(hc, dc, memsize, cudaMemcpyDeviceToHost);
	printf("\nResults: \n");
	for(i = 0; i < n; i++)
		printf("%f + %f = %f\n", ha[i], hb[i], hc[i]);
	cudaFree(da);cudaFree(db);cudaFree(dc);
	free(ha);free(hb);free(hc);
	cudaDeviceSynchronize();
	return 0;
}