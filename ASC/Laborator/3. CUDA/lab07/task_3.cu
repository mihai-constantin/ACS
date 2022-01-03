#include <stdio.h>
#include <math.h>
#include "utils/utils.h"

#define BUF_2M		(2 * 1024 * 1024)
#define BUF_32M		(32 * 1024 * 1024)

int main(void) {
    cudaSetDevice(0);

    int *host_array_a = 0;
    int *host_array_b = 0;

    int *device_array_a = 0;
    int *device_array_b = 0;
    int *device_array_c = 0;

    const int num_bytes = BUF_32M * sizeof(int);

    // TODO 1: Allocate the host's arrays with the specified number of elements:
    // host_array_a => 32M
    // host_array_b => 32M

    host_array_a = (int *) malloc(num_bytes);
    host_array_b = (int *) malloc(num_bytes);

    // TODO 2: Allocate the device's arrays with the specified number of elements:
    // device_array_a => 32M
    // device_array_b => 32M
    // device_array_c => 2M
    cudaMalloc((void **) &device_array_a, num_bytes);
    cudaMalloc((void **) &device_array_b, num_bytes);
    cudaMalloc((void **) &device_array_c, BUF_2M * sizeof(int));

    // Check for allocation errors
    if (!host_array_a || !host_array_b || 
        !device_array_a || !device_array_b || !device_array_c) {
        printf("[*] Error!\n");
        return 1;
    }

    for (int i = 0; i < BUF_32M; ++i) {
        host_array_a[i] = i % 32;
        host_array_b[i] = i % 2;
    }

    printf("Before swap:\n");
    printf("a[i]\tb[i]\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d\t%d\n", host_array_a[i], host_array_b[i]);
    }

    // TODO 3: Copy from host to device
    cudaMemcpy(device_array_a, host_array_a, num_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(device_array_b, host_array_b, num_bytes, cudaMemcpyHostToDevice);

    // TODO 4: Swap the buffers (BUF_2M values each iteration)
    // Hint 1: device_array_c should be used as a temporary buffer
    // Hint 2: cudaMemcpy

    int offset, i;
    for(i = 0; i < BUF_32M / BUF_2M; i++) {
        offset = i * BUF_2M;
        cudaMemcpy(device_array_c + offset, device_array_a + offset, BUF_2M * sizeof(int), cudaMemcpyDeviceToDevice);
        cudaMemcpy(device_array_a + offset, device_array_b + offset, BUF_2M * sizeof(int), cudaMemcpyDeviceToDevice);
        cudaMemcpy(device_array_b + offset, device_array_c + offset, BUF_2M * sizeof(int), cudaMemcpyDeviceToDevice);
    }

    // TODO 5: Copy from device to host
    cudaMemcpy(host_array_a, device_array_a, num_bytes, cudaMemcpyDeviceToHost);
    cudaMemcpy(host_array_b, device_array_b, num_bytes, cudaMemcpyDeviceToHost);

    printf("\nAfter swap:\n");
    printf("a[i]\tb[i]\n");
    for (int i = 0; i < 10; ++i) {
        printf("%d\t%d\n", host_array_a[i], host_array_b[i]);
    }

    // TODO 6: Free the memory
    free(host_array_a);
    free(host_array_b);
    cudaFree(device_array_a);
    cudaFree(device_array_b);
    cudaFree(device_array_c);

    return 0;

}

