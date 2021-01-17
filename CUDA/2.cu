#include <stdio.h>

__global__ void local_mem_GPU(float i) {
	float f;
	f = i;		
	printf("\nMy f value: %f", f);
}

__global__ void global_mem_GPU(float *arr) {
	arr[threadIdx.x] = 2.0f * (float) threadIdx.x;
}

__global__ void shared_mem_GPU(float *arr) {
	int i, idx = threadIdx.x;
	float avg, sum = 0.0f;
	__shared__ float sh_arr[128];
	sh_arr[idx] = arr[idx];
	__syncthreads(); 
	for(i=0; i<idx; i++)
		sum += sh_arr[i];
	avg = sum/(idx+1.0f);
	if(arr[idx]>avg)
		arr[idx] = avg;
}

int main(int argc, char** argv) {
	int i;
	local_mem_GPU<<<1, 128>>>(2.0f);
	float h_arr[128];
	float *d_arr;
	cudaMalloc(&d_arr, sizeof(float)*128);
	cudaMemcpy(d_arr, h_arr, sizeof(float)*128, cudaMemcpyHostToDevice);
	global_mem_GPU<<<1, 128>>>(d_arr);
	cudaMemcpy(h_arr, d_arr, sizeof(float)*128, cudaMemcpyDeviceToHost);	
	printf("\nAfter global execution\n");
	for(i=0; i<128; i++)
		printf(" %lf ", h_arr[i]);
	shared_mem_GPU<<<1, 128>>>(d_arr);
	cudaMemcpy(h_arr, d_arr, sizeof(float)*128, cudaMemcpyDeviceToHost);
	printf("\nAfter shared execution\n");
	for(i=0; i<128; i++)
		printf(" %lf ", h_arr[i]);
	cudaDeviceSynchronize();
	return 0;
}