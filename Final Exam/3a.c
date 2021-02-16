#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int i, a[1000], b[1000];
	long long s;
	for(i = 0; i < 1000; i++)
		a[i] = b[i] = rand()%100;
	#pragma omp parallel for reduction(+:s) 
	for(i = 0; i < 1000; i++)
		s += a[i] + b[i];
	printf("\nSum = %lld", s);
	return 0;
}