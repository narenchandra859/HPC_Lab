#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	int i, n = 1000;
	int a[n];
	for(i = 0; i < n; i++) 
		a[i] = rand() % 50;
	int par_mx = 0;
	#pragma omp parallel shared(a, n) private(i)
	for(i = 0; i < n; i++) {
		printf("\nIn thread %d", omp_get_thread_num());
		#pragma omp critical
		{
			printf("\nThread %d in control of critical section", omp_get_thread_num());
			if(a[i] > par_mx)
				par_mx = a[i];
		}
	}
	int ser_mx;
	for(i = 0; i < n; i++) 
		ser_mx = (a[i] > ser_mx)?a[i]:ser_mx;
	printf("\nMax found by parallel %d, serial %d\n\n", par_mx, ser_mx);
	return 0;
}
