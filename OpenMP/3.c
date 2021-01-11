#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int tid, nthreads, procs, maxthreads, inparallel, dynamicflag, nestedflag;
	#pragma omp parallel private(nthreads, tid) 
	{
		tid = omp_get_thread_num();
		if(tid == 0) {
			nthreads = omp_get_num_threads();
			procs = omp_get_num_procs();
			maxthreads = omp_get_max_threads();
			inparallel = omp_in_parallel();
			dynamicflag = omp_get_dynamic();
			nestedflag = omp_get_nested();
			printf("\nNum threads = %d", nthreads);
			printf("\nIn master thread\nNum procs %d\nMax threads %d\n", procs, maxthreads);
			printf("\nIn parallel region? %d", inparallel);
			printf("\nDynamic threads enabled? %d", dynamicflag);
			printf("\nNested parallelism supported? %d\n\n", nestedflag);
		}
	}
	return 0;
}