#include <stdio.h>
__global__ void hello() {
	printf("\nHello from thread %d in block %d", threadIdx.x, blockIdx.x);
}
int main(int argc, char** argv) {
	hello<<<3,5>>>();
	cudaDeviceSynchronize();
	printf("\n-------------------------------\n");
	hello<<<5,3>>>();
	cudaDeviceSynchronize();
	return 0;
}