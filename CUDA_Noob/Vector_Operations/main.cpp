// Created by : Dani Johanes

#include <cstdlib> 
#include <stdio.h> 
#include "common.cuh"
#include <ctime>
#include <cmath>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

// Global variable
const int SIZE = 20000;
float scaleFactor = 5;
const int ITERS = 1000;
float errorCalc(float* c_cpu, float* c_gpu);

int main() {
	cudaSetDeviceFlags(cudaDeviceMapHost);
	
	bool success;
	float error; // Create for error value
	clock_t start, end;
	float timeCpu, timeGpu;
	float* a;
	float* b;
	float* c_cpu = new float[SIZE];
	float* c_gpu;

	cudaHostAlloc((void**)&a, SIZE * sizeof(float), cudaHostAllocWriteCombined | cudaHostAllocMapped);
	cudaHostAlloc((void**)&b, SIZE * sizeof(float), cudaHostAllocWriteCombined | cudaHostAllocMapped);
	cudaHostAlloc((void**)&c_gpu, SIZE * sizeof(float), cudaHostAllocWriteCombined | cudaHostAllocMapped);

	for (int i = 0; i < SIZE; i++) {
		a[i] = ((float)rand() / (RAND_MAX));
		b[i] = ((float)rand() / (RAND_MAX));
	}
	//Clock started
	start = clock();
	for (int i = 0; i < ITERS; i++) {
		addVectorCPU(a, b, c_cpu, SIZE);
	}
	end = clock(); // End of clock
	
	//CPU timing
	timeCpu = (float)(end - start) * 1000 / (float)CLOCKS_PER_SEC / ITERS;
	printf("Addition by CPU took %f\n", timeCpu);
	success = addVectorGPU(a, b, c_gpu, SIZE);
	if (!success) {
		printf("\n * Device error! * \n");
		return 1;
	}
	
	//Clock started
	start = clock();
	for (int i = 0; i < ITERS; i++) {
		addVectorGPU(a, b, c_gpu, SIZE);
	}
	
	end = clock(); // End of clock
	
	timeGpu = (float)(end - start) * 1000 / (float)CLOCKS_PER_SEC / ITERS;
	printf("Addition by GPU took %f\n", timeGpu);
	printf("Addition speedup = %f\n", timeCpu / timeGpu);
	error = errorCalc(c_cpu, c_gpu);
	printf("Addition Error = %f\n", error);
	printf("\n");
	//Clock started
	start = clock();
	for (int i = 0; i < ITERS; i++) {
		subtractVectorCPU(a, b, c_cpu, SIZE);
	}
	
	end = clock();
	
	timeCpu = (float)(end - start) * 1000 / (float)CLOCKS_PER_SEC / ITERS;
	printf("Subtraction by CPU took %f\n", timeCpu);

	success = subtractVectorGPU(a, b, c_gpu, SIZE);
	if (!success) {
		printf("\n * Device error! * \n");
		return 1;
	}
	start = clock();
	for (int i = 0; i < ITERS; i++) {
		subtractVectorGPU(a, b, c_gpu, SIZE);
	}
	
	end = clock();
	
	timeGpu = (float)(end - start) * 1000 / (float)CLOCKS_PER_SEC / ITERS;
	printf("Subtraction by GPU took %f\n", timeGpu);
	printf("Subtraction speedup = %f\n", timeCpu / timeGpu);
	error = errorCalc(c_cpu, c_gpu);
	printf("Subtraction Error = %f\n", error);
	printf("\n");
	
	start = clock();
	for (int i = 0; i < ITERS; i++) {
		scaleVectorCPU(a, c_cpu, scaleFactor, SIZE);
	}
	
	end = clock();
	//CPU time for vector scaling
	timeCpu = (float)(end - start) * 1000 / (float)CLOCKS_PER_SEC / ITERS;
	printf("Scaling by CPU took %f\n", timeCpu);

	success = scaleVectorGPU(a, c_gpu, scaleFactor, SIZE);
	if (!success) {
		printf("\n * Device error! * \n");
		return 1;
	}
	
	start = clock();
	for (int i = 0; i < ITERS; i++) {
		scaleVectorGPU(a, c_gpu, scaleFactor, SIZE);
	}

	end = clock();
	
	timeGpu = (float)(end - start) * 1000 / (float)CLOCKS_PER_SEC / ITERS;
	printf("Scaling by GPU took %f\n", timeGpu);
	printf("Scaling speedup = %f\n", timeCpu / timeGpu);
	error = errorCalc(c_cpu, c_gpu);
	printf("Scaling Error = %f\n", error);

	cudaFreeHost(a);
	cudaFreeHost(b);
	cudaFreeHost(c_gpu);
	delete[] c_cpu;
	return 0;
}

float errorCalc(float* c_cpu, float* c_gpu) {
	float sum = 0, delta = 0;
	for (int i = 0; i < SIZE; i++) {
		delta += (c_cpu[i] - c_gpu[i]) * (c_cpu[i] - c_gpu[i]);
		sum += (c_cpu[i] * c_gpu[i]);
	}
	float L2norm = sqrt(delta / sum);
	return L2norm;
}