#include <stdio.h>
#include "utils/utils.h"

// ~TODO 3~
// Modify the kernel below such as each element of the 
// array will be now equal to 0 if it is an even number
// or 1, if it is an odd number
__global__ void kernel_parity_id(int *a, int N) {

    // global element index for current thread
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;

    if(i < N) {

        a[i] = a[i] % 2;
    }

}

// ~TODO 4~
// Modify the kernel below such as each element will
// be equal to the BLOCK ID this computation takes
// place.
__global__ void kernel_block_id(int *a, int N) {

    // global element index for current thread
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;
    
    if (i < N) {
        a[i] = blockIdx.x;
    }
}

// ~TODO 5~
// Modify the kernel below such as each element will
// be equal to the THREAD ID this computation takes
// place.
__global__ void kernel_thread_id(int *a, int N) {

    // global element index for current thread
    unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;

    if(i < N) {
        a[i] = threadIdx.x;
    }
}

int main(void) {
    int nDevices;

    // Get the number of CUDA-capable GPU(s)
    cudaGetDeviceCount(&nDevices);
    printf("[HOST] You have %d CUDA-capable GPU(s)\n", nDevices);

    // ~TODO 1~
    // For each device, show some details in the format below, 
    // then set as active device the first one (assuming there
    // is at least CUDA-capable device). Pay attention to the
    // type of the fields in the cudaDeviceProp structure.
    //
    // Device number: <i>
    //      Device name: <name>
    //      Total memory: <mem>
    //      Memory Clock Rate (KHz): <mcr>
    //      Memory Bus Width (bits): <mbw>
    // 
    // Hint: look for cudaGetDeviceProperties and cudaSetDevice in
    // the Cuda Toolkit Documentation. 
    for (int i = 0; i < nDevices; ++i) {
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, i);

        printf("Device number: %d\n", i);
        printf("\tDevice name: %s\n", deviceProp.name);
        printf("\tTotal global memory: %zu\n", deviceProp.totalGlobalMem);
        printf("\tMemory Clock Rate(KHz): %d\n", deviceProp.clockRate);
        printf("\tMemory Bus Width (bits): %d\n", deviceProp.memoryBusWidth);
    }

    cudaSetDevice(0);

    // ~TODO 2~
    // With information from example_2.cu, allocate an array with
    // integers (where a[i] = i). Then, modify the three kernels
    // above and execute them using 4 blocks, each with 4 threads.
    // Hint: num_elements = block_size * block_no (see example_2)
    //
    // You can use the fill_array_int(int *a, int n) function (from utils)
    // to fill your array as many times you want.
    const int num_elements = 16;
    const int num_bytes = num_elements * sizeof(int);

    // declaring host and device arrays
    int *host_array = 0;
    int *device_array = 0;

    // alocate the host array
    host_array = (int *) malloc(num_bytes);

    // alocate the device's array
    cudaMalloc((void **) &device_array, num_bytes);

    if (!host_array || !device_array) {
        printf("[HOST] Couldn't allocate memory\n");
        return 1;
    }

    // initialize the host array
    fill_array_int(host_array, num_elements);

    // copy from host(cpu/ram) to device(gpu/vram)
    cudaMemcpy(device_array, host_array, num_bytes, cudaMemcpyHostToDevice);

    // ~TODO 3~
    // Execute kernel_parity_id kernel and then copy from 
    // the device to the host; call cudaDeviceSynchronize()
    // after a kernel execution for safety purposes.
    //

    kernel_parity_id<<<4, 4>>>(device_array, num_elements);
    cudaDeviceSynchronize();
    
    cudaMemcpy(host_array, device_array, num_bytes, cudaMemcpyDeviceToHost);
    check_task_1(3, host_array);

    // ~TODO 4~
    // Execute kernel_block_id kernel and then copy from 
    // the device to the host;
    //

    kernel_block_id<<<4,4>>>(device_array, num_elements);
    cudaDeviceSynchronize();

    cudaMemcpy(host_array, device_array, num_bytes, cudaMemcpyDeviceToHost);
    check_task_1(4, host_array);

    // ~TODO 5~
    // Execute kernel_thread_id kernel and then copy from 
    // the device to the host;
    //

    kernel_thread_id<<<4, 4>>>(device_array, num_elements);
    cudaDeviceSynchronize();

    cudaMemcpy(host_array, device_array, num_bytes, cudaMemcpyDeviceToHost);
    check_task_1(5, host_array);

    // TODO 6: Free the memory
    free(host_array);
    cudaFree(device_array);
    
    return 0;
}