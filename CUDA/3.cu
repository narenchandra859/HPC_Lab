#include <stdio.h>
#define NUM_BLOCKS 32
#define BLOCK_WIDTH 5
__global__ void hello() {
	printf("\nThread %d in block %d", threadIdx.x, blockIdx.x);
}
int main(int argc, char** argv) {
	hello<<<NUM_BLOCKS, BLOCK_WIDTH>>>();
	cudaDeviceSynchronize();
	printf("\nDone\n");
	return 0;
}
