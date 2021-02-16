#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int i, tid, chunk = 10;
	double a[100], b[100], c[100];
	for(i = 0; i < 100; i++) 
		a[i] = b[i] = rand() % 100;
	#pragma omp parallel shared(chunk, a, b, c) private(i, tid) 
	{
		tid = omp_get_thread_num();
		if(tid == 0)
			printf("\nStarting with %d threads", omp_get_num_threads());
		#pragma omp for schedule(dynamic, chunk)
		for(i = 0; i < 100; i++)  {
			printf("\nThread %d at index %d", tid, i);
			c[i] = a[i] + b[i];
		}
	}
	printf("\nResult\n");
	for(i = 0; i < 100; i++) 
		printf("%.2lf + %.2lf=%.2lf\n", a[i], b[i], c[i]);
	return 0;
}