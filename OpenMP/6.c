#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
// sieve to find primes
int main(int argc, char **argv)
{
	long long n = 100000000;
	long long *a = (long long*)malloc((n+1)*sizeof(long long));
	long long i, k = 2, found, pcount;
	double t1 = omp_get_wtime(), t2;
	#pragma omp parallel for 
	for(int i = 0; i < n; ++i) a[i] = 1;
	#pragma omp parallel shared(n) firstprivate(k) private(i, found)
	while (k * k <= n)
	{
		#pragma omp for
		for (i = k * k; i <= n; i += k)
			a[i] = 0;
		found = 0;
		for (i = k + 1; found!=1; i++) {
			if (a[i]) {
				k = i;
				found = 1;
			}
		}
	}
	t2 = omp_get_wtime();
	printf("\n\nTime taken: %.2f seconds\n", t2 - t1);
	pcount = 0;
	for (i = 2; i <= n; i++)
		if(a[i]) pcount++;
  printf("\n%lld primes between 0 and %lld\n", pcount, n);
  return 0;
}