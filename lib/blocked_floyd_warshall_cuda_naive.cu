#include <cuda.h>
#include <cuda_runtime.h>
#include <driver_functions.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
extern "C" {
    #include "blocked_floyd_warshall.h"
}

__forceinline__
__host__ int check_cuda_error(t_error* err) {
	cudaError_t errCode = cudaPeekAtLastError();
	if (errCode != cudaSuccess) {
		err->err_code = errCode;
		snprintf(err->err_msg, sizeof(err->err_msg), "%s", cudaGetErrorString(errCode));
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

__forceinline__
__device__ void calc(int* graph, int n, int k, int i, int j) {
	if ((i >= n) || (j >= n) || (k >= n)) return;
	const unsigned int kj = k * n + j;
	const unsigned int ij = i * n + j;
	const unsigned int ik = i * n + k;
	int t1 = graph[ik] + graph[kj];
	int t2 = graph[ij];
	graph[ij] = (t1 < t2) ? t1 : t2;
}

__global__ void floyd_warshall_naive_kernel(int n, int k, int* graph) {
	const unsigned int i = blockIdx.y * blockDim.y + threadIdx.y;
	const unsigned int j = blockIdx.x * blockDim.x + threadIdx.x;
	calc(graph, n, k, i, j);
}

extern "C"
__host__ int blocked_floyd_warshall(int* graph, int n, int b, int* apsp, t_error* err) {

	if (n <= 0) {
		err->err_code = WRONG_NUM_OF_NODES_ERR;
		char err_msg[100] = {
				"The number of nodes should be > 0"};
		snprintf(err->err_msg, sizeof(err->err_msg), "%s", err_msg);
		return EXIT_FAILURE;
	}

	if (b <= 0 || b > n) {
		err->err_code = WRONG_BLOCK_SIZE_ERR;
		char err_msg[100] = {
				"The number of blocks b should be: 0 < b <= n, where n is the number of nodes"};
		snprintf(err->err_msg, sizeof(err->err_msg), "%s", err_msg);
		return EXIT_FAILURE;
	}
	const size_t size = n * n * sizeof(int);
	int* device_graph;

	cudaMalloc(&device_graph, size);
	cudaMemcpy(device_graph, graph,  size, cudaMemcpyHostToDevice);

	dim3 block_dim(b, b, 1);
    dim3 grid_dim((n + block_dim.x - 1) / block_dim.x,
                  (n + block_dim.y - 1) / block_dim.y);

    int k;
	for (k = 0; k < n; k++) {
		floyd_warshall_naive_kernel<<<grid_dim, block_dim>>>(n, k, device_graph);
		cudaDeviceSynchronize();
	}

	cudaMemcpy(apsp, device_graph, size, cudaMemcpyDeviceToHost);
	cudaFree(device_graph);

	return check_cuda_error(err);
}
