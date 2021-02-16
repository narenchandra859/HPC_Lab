#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	srand(time(NULL));
	int n = 100, i, a[n];
	for(i = 0; i < n; i++)
		a[i] = rand() % 10000;
	int mx = -1;
	#pragma omp parallel for shared(a) 
	for(i = 0; i < n; i++) {
		#pragma omp critical
		{
			if(a[i] > mx)
				mx = a[i];
		}
	}
	int smx = -1;
	for(i = 0; i < n; i++)
		smx = a[i] > smx ? a[i]:smx;
	printf("\nSerial max = %d\tParallel max = %d\n", smx, mx);
	return 0;
}