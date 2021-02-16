#include <stdio.h>
#define NUM_BLOCK 3	
#define BLOCK_WIDTH 5

__global__ void hello() {
	printf("\nHello world. Thread %d in block %d", threadIdx.x, blockIdx.x);
}

int main(int argc, char** argv) {
	hello<<<NUM_BLOCK, BLOCK_WIDTH>>>();
	cudaDeviceSynchronize();
	printf("\nDone");
	return 0;
}