#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int SIZE = 1000;
	int i, tid;
	double a[SIZE], b[SIZE], c[SIZE], d[SIZE];
	for(i = 0; i < SIZE; i++) {
		a[i] = rand() % 100;
		b[i] = rand() % 100;
		c[i] = d[i] = 0;
	}
	#pragma omp parallel shared(a, b, c, d, SIZE) private(tid, i) 
	{
		tid = omp_get_thread_num();
		if(tid == 0)
			printf("\nStarting with %d threads", omp_get_num_threads());
		#pragma omp sections nowait 
		{
			#pragma omp section
			{
				for(i = 0; i < SIZE; i++) {
					c[i] = a[i] + b[i];
					printf("\nThread %d doing C=A+B at index %d", tid, i);
				}
			}
			#pragma omp section
			{
				for(i = 0; i < SIZE; i++) {
					d[i] = a[i] - b[i];
					printf("\nThread %d doing D=A-B at index %d", tid, i);
				}
			}
		}
	}
	printf("\nResults: \n");
	for(i = 0; i < SIZE; i++) 
		printf("\n%lf + %lf = %lf\t%lf + %lf = %lf",a[i],b[i],c[i],a[i],b[i],d[i]);
	printf("\nDone\n\n");
	return 0;
}
