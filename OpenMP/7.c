#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int a, b;
#pragma omp threadprivate(a)

int main(int argc, char** argv) {
	printf("\nVariable 'a' is threadprivate, variable 'b' is just private\n\n");
	printf("\n1st Parallel Region: \n");
	#pragma omp parallel private(b)
	{
		a = 100;
		b = 100;
		printf("\nInitializing a=100 and b=100 in region 1");
		printf("\nIn region 1 (thread %d): a = %d, b = %d", omp_get_thread_num(), a, b);
	}
	printf("\n2nd Parallel Region: \n");
	#pragma omp parallel private(b)
	{
		printf("\nIn region 2 (thread %d): a = %d, b = %d", omp_get_thread_num(), a, b);
	}
	printf("\nVariable 'a' persists (each thread has its own instance), 'b' doesn't (random value/not initialized in region 2)\n\n");
	return 0;
}