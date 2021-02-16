#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define n 3

int main(int argc, char** argv) {
	int a[n][n], b[n][n], c[n][n];
	int tid, i, j, k;
	int chunk = 5;
	#pragma omp parallel shared(a, b, c) private(i, j, k)
	{
		#pragma omp for schedule(dynamic, chunk)
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				a[i][j] = rand()%100;
				b[i][j] = rand()%100;
				c[i][j] = 0;
			}
		}
		#pragma omp for schedule(dynamic, chunk)
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				for(k = 0; k < n; k++) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
	}
	printf("\nResults: \n");
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) 
			printf("(%d,%d,%d)\t",a[i][j],b[i][j],c[i][j]);
		printf("\n");
	}
	return 0;
}