#include <iostream>

using namespace std;

static void HandleError(cudaError_t err, const char *file, int line ) {
    if (err != cudaSuccess) {
        cout << cudaGetErrorString(err) << " in " 
            << file << " at line " << line << endl;
        exit( EXIT_FAILURE );
    }
}
#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

//#define MAGNITUDE       (1)
#define MAGNITUDE       (1024 * 1024)
#define NUM_BLOCKS      8 * MAGNITUDE
#define NUM_THREADS     16
#define NUM_ELEM        100 * MAGNITUDE

__global__ void kernel_compute(int* data) {
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
    // invalid access
    data[idx] = 1111 * idx;
}

int main(int argc, char *argv[]) {
    int* data = NULL;

    HANDLE_ERROR( cudaMalloc(&data, 1 * sizeof(int)) );

    // launch kernel
    kernel_compute<<<NUM_BLOCKS, NUM_THREADS>>>(data);
    HANDLE_ERROR( cudaDeviceSynchronize() );

    return 0;
}