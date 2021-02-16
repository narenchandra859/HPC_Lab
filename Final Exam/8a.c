#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int f1 = 1, f2 = 1;
	int i, n = 10;
	int fact1 = 1, fact2 = 1;
	#pragma omp parallel for private(f1) shared(fact1)
	for(i = f1; i < n; i++)
	{
		#pragma omp critical
		fact1 *= i;
	}
	#pragma omp parallel for firstprivate(f2) shared(fact2)
	for(i = f2; i < n; i++)
	{
		#pragma omp critical
		fact2 *= i;
	}
	printf("\nUsing private fact(%d) = %d\nUsing firstprivate fact(%d) = %d\n", n, fact1, n, fact2);
	return 0;	
}