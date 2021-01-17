#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int i, n = 10;
	int a[n];
	for(i = 0; i < n; i++) 
		a[i] = rand() % 50;
	int par_mx = 0;
	omp_lock_t MAXLOCK;
	omp_init_lock(&MAXLOCK);
	#pragma omp parallel for 
	for(int i = 0; i < n; ++i)
	{
		printf("\nThread %d", omp_get_thread_num());
		omp_set_lock(&MAXLOCK);
		if(a[i] > par_mx) par_mx = a[i];
		omp_unset_lock(&MAXLOCK);
	}
	omp_destroy_lock(&MAXLOCK);
	int ser_mx;
	for(i = 0; i < n; i++) 
		ser_mx = (a[i] > ser_mx)?a[i]:ser_mx;
	printf("\nMax found by parallel %d, serial %d\n\n", par_mx, ser_mx);
	return 0;
}
