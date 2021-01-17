#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int tid, i, chunk, n = 100;
	int a[n], b[n], c[n];
	for(i = 0; i < n; i++) 
		a[i] = b[i] = rand() % 100;
	chunk = 10;
	#pragma omp parallel shared(a, b, c, chunk) private(i, tid)
	{
		tid = omp_get_thread_num();
		if(tid == 0) {
			printf("\nStarting with %d threads..", omp_get_num_threads());
		}
		#pragma omp for schedule(dynamic, chunk)
		for(i = 0; i < n; i++) {
			printf("\nThread %d at index %d", tid, i);
			c[i] = a[i] + b[i];
		}
	}
	return 0;
}
