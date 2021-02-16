#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int tid, nthreads, nproc, maxthreads, dyn, par, nested;
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		if(tid == 0) {
			printf("\nNumber of threads: %d", omp_get_num_threads());
			printf("\nMax threads: %d", omp_get_max_threads());
			printf("\nNumber of processors: %d", omp_get_num_procs());
			printf("\nDynamic threads enabled: %d", omp_get_dynamic());
			printf("\nParallel region: %d", omp_in_parallel());
			printf("\nNested parallelism enabled: %d\n", omp_get_nested());
		}
	}
	return 0;
}