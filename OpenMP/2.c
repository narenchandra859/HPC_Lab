#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv) {
	int tid, nthreads = 4, i, j;
	long long n = 15;
	long long *x;
	x = (long long *)malloc(n*sizeof(long long));
	if(argc > 1) {
		nthreads = atoi(argv[1]);
		if(omp_get_dynamic()) omp_set_dynamic(0);
	}
	omp_set_num_threads(nthreads);
	printf("\nStarting with %d threads", nthreads);
	j = 1;
	#pragma omp parallel for private(tid) firstprivate(x, j)
	for(i = 1; i <= n; i++) {
		tid = omp_get_thread_num();
		printf("\nThread %d", tid);
		x[i] = x[i-1]*i;	
	}
	printf("\nFactorials:\n");
	for(i = 0; i <= n; i++)
		printf("\nFactorial %d = %lld", i, x[i]);
	return 0;
}