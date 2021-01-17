#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int f1 = 1, fact1 = 1;
	int f2 = 1, fact2 = 1;
	int n = 10;
	int i;
	#pragma omp parallel for private(f1) shared(n, fact1)
	for(i = f1; i <= n; i++) {
		#pragma omp critical
		fact1 *= i;
	}

	printf("\nFactorial(%d) = %d (with private)", n, fact1);
	#pragma omp parallel for firstprivate(f2) shared(n, fact2)
	for(i = f2; i <= n; i++) {
		#pragma omp critical
		fact2 *= i;
		printf("\nl2 %d %d", i, fact2);
	}
	printf("\nFactorial (%d) = %d (with firstprivate)\n", n, fact2);
	return 0;
}
