#include <stdio.h>
#include <cstdlib>
#include <mm_malloc.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

#define GRIDSIZE 128
#define BLOCKSIZE 16

cudaEvent_t start, stop;
timeval t;

void fillMatrices (float **m1, float **m2, float **result, int N) {
	*m1 = (float *)_mm_malloc(N*N * sizeof(float), 32);
    *m2 = (float *)_mm_malloc(N*N * sizeof(float), 32);
    *result = (float *)_mm_malloc(N*N * sizeof(float), 32);

	srand(time(NULL));

	for (unsigned i = 0; i < N*N; i++) {
		(*m1)[i] = (float) rand();
		(*m2)[i] = 1.0;
	}
}

int validate(float *m, int N) {
    for(unsigned i = 0; i < N*N; i += N) {
        float aux = m[i];
        for(unsigned j = 0; j < N; j++) {
            if(m[i + j] != aux) 
				return 0;
        }
    }
    return 1;
}

void startKernelTime (void) {
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);
}

void stopKernelTime (void) {
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    
	float milliseconds = 0;
    cudaEventElapsedTime(&milliseconds, start, stop);

    cout << milliseconds << " ms" << endl;
}

void checkCUDAError (const char *msg) {
	cudaError_t err = cudaGetLastError();
	if( cudaSuccess != err) {
		cerr << "Cuda error: " << msg << ", " << cudaGetErrorString( err) << endl;
		exit(-1);
	}
}

__global__
void matrixMultKernel (float *dev_m1, float *dev_m2, float *dev_res, int N) {
    __shared__ float tileM1[BLOCKSIZE][BLOCKSIZE];
    __shared__ float tileM2[BLOCKSIZE][BLOCKSIZE];

    int i = blockIdx.y * BLOCKSIZE + threadIdx.y;
    int j = blockIdx.x * BLOCKSIZE + threadIdx.x;
    float aux = 0;
    int idx;

    if (i < N && j < N){
		for (int kk = 0; kk < GRIDSIZE; kk++){
        	idx = i * N + (kk * BLOCKSIZE + threadIdx.x);

        	if (idx >= N * N)
            	tileM1[threadIdx.y][threadIdx.x] = 0;
        	else
            	tileM1[threadIdx.y][threadIdx.x] = dev_m1[idx];

        	idx = (kk * BLOCKSIZE + threadIdx.y) * N + j;

        	if (idx >= N * N)
            	tileM2[threadIdx.y][threadIdx.x] = 0;
        	else
            	tileM2[threadIdx.y][threadIdx.x] = dev_m2[idx];

        	__syncthreads();

        	for (int k = 0; k < BLOCKSIZE; k++)
            	aux += tileM1[threadIdx.y][k] * tileM2[k][threadIdx.x];
				
        	__syncthreads();
    	}

        dev_res[i * N + j] = aux;
    }
}

void matrixMultGPU (float *m1, float *m2, float *result, int N) {

    float *dev_m1, *dev_m2, *dev_res;

    cudaMalloc((void **)&dev_m1, N*N * sizeof(float));
    cudaMalloc((void **)&dev_m2, N*N * sizeof(float));
	cudaMalloc((void **)&dev_res, N*N * sizeof(float));

    startKernelTime();
    cudaMemcpy(dev_m1, m1, N*N * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_m2, m2, N*N * sizeof(float), cudaMemcpyHostToDevice);
	checkCUDAError("Error using cudaMemcpyHostToDevice");
    stopKernelTime();

	dim3 dimGrid(GRIDSIZE, GRIDSIZE);
	dim3 dimBlock(BLOCKSIZE, BLOCKSIZE);

    startKernelTime();
    matrixMultKernel <<< dimGrid, dimBlock >>> (dev_m1, dev_m2, dev_res, N);
    stopKernelTime();

    startKernelTime();
	cudaMemcpy(result, dev_res, N*N * sizeof(float), cudaMemcpyDeviceToHost);
    checkCUDAError("Error using cudaMemcpyHostToDevice");
    stopKernelTime();

    cudaFree(dev_m1);
    cudaFree(dev_m2);
	cudaFree(dev_res);
}

int main (int argc, char** argv) {

	if(argc < 2)
		return 1;
	
	int N = atoi(argv[1]);
	float *m1, *m2, *result;

	fillMatrices (&m1, &m2, &result, N);

	matrixMultGPU (m1, m2, result, N);

	cout << validate(result, N) << endl;

	return 0;
}