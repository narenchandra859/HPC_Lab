#include <stdio.h>

__global__ void local_mem_GPU(float i) {
<<<<<<< Updated upstream
	float f;	// f is local
	f = i;		// f and i private to EACH thread
=======
	float f;
	f = i;		
>>>>>>> Stashed changes
	printf("\nMy f value: %f", f);
}

__global__ void global_mem_GPU(float *arr) {
<<<<<<< Updated upstream
	// array is ptr to global memory on device
=======
>>>>>>> Stashed changes
	arr[threadIdx.x] = 2.0f * (float) threadIdx.x;
}

__global__ void shared_mem_GPU(float *arr) {
<<<<<<< Updated upstream
	// local vars private to each thread
	int i, idx = threadIdx.x;
	float avg, sum = 0.0f;
	//shared visible to all threads in thread block
	__shared__ float sh_arr[128];
	//global arr to shared mem arr
	//each thread copies ONE element at idx
	sh_arr[idx] = arr[idx];
	__syncthreads(); //all writes completed check
=======
	int i, idx = threadIdx.x;
	float avg, sum = 0.0f;
	__shared__ float sh_arr[128];
	sh_arr[idx] = arr[idx];
	__syncthreads(); 
>>>>>>> Stashed changes
	for(i=0; i<idx; i++)
		sum += sh_arr[i];
	avg = sum/(idx+1.0f);
	if(arr[idx]>avg)
		arr[idx] = avg;
<<<<<<< Updated upstream
	//above change can be seen by HOST/other thread blocks
=======
>>>>>>> Stashed changes
}

int main(int argc, char** argv) {
	int i;
<<<<<<< Updated upstream
	// demonstrate local mem
	local_mem_GPU<<<1, 128>>>(2.0f);
	// demonstrate global mem
	float h_arr[128]; // host
=======
	local_mem_GPU<<<1, 128>>>(2.0f);
	float h_arr[128];
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
}
=======
}
>>>>>>> Stashed changes
