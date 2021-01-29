#include <cuda.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>
#include <stdio.h>
#include "common.cuh"
#include "math.h"

const float TILE_SIZE = 1024;

__global__ void VectoraddKernel(float* Agpu, float* Bgpu, float* Cgpu, int size){
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if (tid < size) {
		Cgpu[tid] = Agpu[tid] + Bgpu[tid];
	}
}

__global__ void VectorsubtractKernel(float* Agpu, float* Bgpu, float* Cgpu, int size){
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if (tid < size) {
		Cgpu[tid] = Agpu[tid] - Bgpu[tid];
	}
}

__global__ void VectorscaleKernel(float* Agpu, float* Cgpu, float scaling, int size){
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if (tid < size) {
		Cgpu[tid] = Agpu[tid] * scaling;
	}
}

bool addVectorGPU(float* M, float* N, float* P, int size) {
	int bytes = size * sizeof(float);
	float* Agpu, * Bgpu, * Cgpu;
	
	cudaHostGetDevicePointer((void**)&Agpu, M, 0);
	cudaHostGetDevicePointer((void**)&Bgpu, N, 0);
	cudaHostGetDevicePointer((void**)&Cgpu, P, 0);
	
	dim3 dimBlock(TILE_SIZE);
	dim3 dimGrid((int)ceil((float)size / (float)TILE_SIZE));
	
	VectoraddKernel << <dimGrid, dimBlock >> > (Agpu, Bgpu, Cgpu, size);
	cudaThreadSynchronize();
	
	cudaError_t status = cudaGetLastError();
	if (status != cudaSuccess) {
		printf("Kernel failed: %s", cudaGetErrorString(status));
		return false;
	}
	return true;
}

bool subtractVectorGPU(float* M, float* N, float* P, int size) {
	int bytes = size * sizeof(float);
	float* Agpu, * Bgpu, * Cgpu;
	
	cudaHostGetDevicePointer((void**)&Agpu, M, 0);
	cudaHostGetDevicePointer((void**)&Bgpu, N, 0);
	cudaHostGetDevicePointer((void**)&Cgpu, P, 0);
	
	dim3 dimBlock(TILE_SIZE);
	dim3 dimGrid((int)ceil((float)size / (float)TILE_SIZE));
	
	VectorsubtractKernel << <dimGrid, dimBlock >> > (Agpu, Bgpu, Cgpu, size);
	cudaThreadSynchronize();
	//Return error if any 
	cudaError_t status = cudaGetLastError();
	if (status != cudaSuccess) {
		printf("Kernel failed: %s", cudaGetErrorString(status));
		return false;
	}

	return true;
}

bool scaleVectorGPU(float* M, float* P, float scaling, int size) {
	int bytes = size * sizeof(float);
	float* Agpu, * Cgpu;
	
	cudaHostGetDevicePointer((void**)&Agpu, M, 0);
	cudaHostGetDevicePointer((void**)&Cgpu, P, 0);
	
	dim3 dimBlock(TILE_SIZE);
	dim3 dimGrid((int)ceil((float)size / (float)TILE_SIZE));
	
	VectorscaleKernel << <dimGrid, dimBlock >> > (Agpu, Cgpu, scaling, size);
	cudaThreadSynchronize();
	
	cudaError_t status = cudaGetLastError();
	if (status != cudaSuccess) {
		printf("Kernel failed: %s", cudaGetErrorString(status));
		return false;
	}

	return true;
}