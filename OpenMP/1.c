#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define nra 3
#define nca 3
#define ncb 3
int main(int argc, char** argv) {
	int tid, nthreads, i, j, k, chunk;
	double a[nra][nca], b[nca][ncb], c[nra][ncb];
	chunk = 10;
	#pragma omp parallel shared(a, b, c, nthreads, chunk) private(tid, i, j, k) 
	{
		tid = omp_get_thread_num();
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("\nStart with %d threads", nthreads);
		}
		#pragma omp for schedule(static, chunk)
		for(i = 0; i < nra; i++) 
			for(j = 0; j < nca; j++) {
				printf("\nThread %d init matrix A", tid);
				a[i][j] = i+j;
			}
		#pragma omp for schedule(static, chunk)
		for(i = 0; i < nca; i++) 
			for(j = 0; j < ncb; j++) {
				printf("\nThread %d init matrix B", tid);
				b[i][j] = i*j;
			}
		#pragma omp for schedule(static, chunk)
		for(i = 0; i < nra; i++) 
			for(j = 0; j < ncb; j++) {
				printf("\nThread %d init matrix C", tid);
				c[i][j] = 0;
			}
		#pragma omp for schedule(static, chunk)
		for(i = 0; i < nra; i++) {
			printf("\nThread %d calculating row %d", tid, i);
			for(j = 0; j < ncb; j++) 
				for(k = 0; k < nca; k++)
					c[i][j] += a[i][k] * b[k][j];
		}
	}
	printf("\nResults: \n");
	for(i = 0; i < nra; i++) {
		for(j = 0; j < ncb; j++) 
			printf("%.2f ", c[i][j]);
		printf("\n");
	}
	return 0;
}