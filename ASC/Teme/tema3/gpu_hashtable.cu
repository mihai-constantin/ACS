#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <string>

#include "gpu_hashtable.hpp"

/*
 *	hash function
 */
__device__ int getHashCode(int key, int capacity) {
	return ((long long)abs(key) * 1646237llu) % 67965551447llu % capacity;
}

__global__ void kernel_insert(int *keys, int *values, int N, HashTable hashtable) {

	/* compute the global element index this thread should process */
	int i = threadIdx.x + blockIdx.x * blockDim.x;

	/* avoid accessing out of bounds elements */
	if (i < N) {

		/* get start index for current key based by current capacity of the hashtable */
		int idx = getHashCode(keys[i], hashtable.capacity);

		/* 
		 * iterate through hashtable to find a free slot for insertion 
		 * use atomicCAS for threads synchronization
		 * if current key is 0, set its key to keys[i] and its value to values[i]
		 * if current key is keys[i], update its value
		 */

		/* iterate through [idx, hashtable.capacity) positions */
		for (int k = idx; k < hashtable.capacity; k++) {
			int old_key = atomicCAS(&hashtable.nodes[k].key, 0, keys[i]);
			if (!old_key || old_key == keys[i]) {
				hashtable.nodes[k].value = values[i];
				return;
			}
		}

		/* iterate through [0, idx) positions */
		for (int k = 0; k < idx; k++) {
			int old_key = atomicCAS(&hashtable.nodes[k].key, 0, keys[i]);
			if (!old_key || old_key == keys[i]) {
				hashtable.nodes[k].value = values[i];
				return;
			}
		}
	}
}

__global__ void kernel_reshape(HashTable old_hashtable, HashTable new_hashtable) {

	/* compute the global element index this thread should process */
	int i = threadIdx.x + blockIdx.x * blockDim.x;

	/* avoid accessing out of bounds elements */
	if (i < old_hashtable.capacity) {

		/* verify if there is a key at index */
		if (old_hashtable.nodes[i].key != 0) {

			/* get start index for current key based by capacity of the new hashtable */
			int idx = getHashCode(old_hashtable.nodes[i].key, new_hashtable.capacity);

			/* 
			 * iterate through hashtable to find a free slot for insertion 
			 * use atomicCAS for threads synchronization
			 */
			 
			/*
			 * if current key from new_hashtable is 0, 
			 * set its key to old_hashtable.nodes[i].key 
			 * and its value to old_hashtable.nodes[i].value
			 */

			/* iterate through [idx, new_hashtable.capacity) positions */
			for (int k = idx; k < new_hashtable.capacity; k++) {
				int old_key = atomicCAS(&new_hashtable.nodes[k].key, 0, old_hashtable.nodes[i].key);
	
				if (!old_key) {
					new_hashtable.nodes[k].value = old_hashtable.nodes[i].value;
					return;
				}
			}
	
			/* iterate through [0, idx) positions */
			for (int k = 0; k < idx; k++) {
				int old_key = atomicCAS(&new_hashtable.nodes[k].key, 0, old_hashtable.nodes[i].key);
	
				if (!old_key) {
					new_hashtable.nodes[k].value = old_hashtable.nodes[i].value;
					return;
				}
			}
		}
	}
}

__global__ void kernel_get(int *keys, int *values, int N, HashTable hashtable) {
	/* compute the global element index this thread should process */
	int i = threadIdx.x + blockIdx.x * blockDim.x;

	/* avoid accessing out of bounds elements */
	if (i < N) {

		/* get start index for current key based by current capacity of the hashtable */
		int idx = getHashCode(keys[i], hashtable.capacity);

		/* 
		 * iterate through hashtable to find the key
		 * set values[i] to corresponding value of the key
		 */

		/* iterate through [idx, hashtable.capacity) positions */
		for (int k = idx; k < hashtable.capacity; k++) {
			if (hashtable.nodes[k].key == keys[i]) {
				values[i] = hashtable.nodes[k].value;
				return;
			}
		}

		/* iterate through [0, idx) positions */
		for (int k = 0; k < idx; k++) {
			if (hashtable.nodes[k].key == keys[i]) {
				values[i] = hashtable.nodes[k].value;
				return;
			}
		}
	}

}

/* INIT HASH */
GpuHashTable::GpuHashTable(int size) {

	/* initially, we don't have any elements inserted into hashtable */
	hashtable.size = 0;
	
	/* set initial capacity to given size parameter */
	hashtable.capacity = size;

	const int num_bytes = size * sizeof(Node);

	/* alloc memory for nodes vector */
	cudaMalloc(&hashtable.nodes, num_bytes);
	if (!hashtable.nodes) {
		return;
	}

	/* initially, set nodes vector to 0 */
	cudaMemset(hashtable.nodes, 0, num_bytes);
}

/* DESTROY HASH */
GpuHashTable::~GpuHashTable() {
	/* free memory used by nodes vector */
	cudaFree(hashtable.nodes);
}

/* RESHAPE HASH */
void GpuHashTable::reshape(int numBucketsReshape) {

	HashTable new_hashtable;
	
	/* set new capacity such that load factor remains to 80% */	
	new_hashtable.capacity = (int)(numBucketsReshape / 0.8f);

	/* set new size to current hashtable's size */
	new_hashtable.size = hashtable.size;

	const int num_bytes = new_hashtable.capacity * sizeof(Node);

	/* alloc memory for nodes vector */
	cudaMalloc(&new_hashtable.nodes, num_bytes);
	if (!new_hashtable.nodes) {
		return;
	}

	/* initially, set nodes vector to 0 */
	cudaMemset(new_hashtable.nodes, 0, num_bytes);

	/*
	 *	Compute the parameters necessary to run the kernel
	 *	- the number of blocks
	 *  - the number of threads per block 
	 */

	unsigned int blocks_no = hashtable.capacity / 1024;

	/* deal with a possible partial final block */
	if (hashtable.capacity % 1024) {
		++blocks_no;
	}

	/* execute the kernel */
	kernel_reshape <<< blocks_no, 1024 >>> (hashtable, new_hashtable);

	cudaDeviceSynchronize();

	/* free memory used by nodes vector */
	cudaFree(hashtable.nodes);

	/* set hashtable to new_hashtable */
	hashtable = new_hashtable;
}

/* INSERT BATCH */
bool GpuHashTable::insertBatch(int *keys, int* values, int numKeys) {

	const int num_bytes = numKeys * sizeof(int);

	int *device_keys = 0;
	int *device_values = 0;

	/* allocate the device's arrays */
	cudaMalloc(&device_keys, num_bytes);
	cudaMalloc(&device_values, num_bytes);

	if (!device_keys || !device_values) {
		/* could not allocate enough memory */
		return false;
	}

	/* reshape if necessary */
	float new_factor = (float)(hashtable.size + numKeys) / (float)hashtable.capacity;
	if (new_factor > 0.8f) {
		reshape(hashtable.size + numKeys);
	}

	/* copy from host(cpu/ram) to device(gpu/vram) */
	cudaMemcpy(device_keys, keys, num_bytes, cudaMemcpyHostToDevice);
	cudaMemcpy(device_values, values, num_bytes, cudaMemcpyHostToDevice);

	/*
	 *	Compute the parameters necessary to run the kernel
	 *	- the number of blocks
	 *  - the number of threads per block 
	 */
	
	unsigned int blocks_no = numKeys / 1024;

	/* deal with a possible partial final block */
	if (numKeys % 1024) {
		++blocks_no;
	}

	/* execute the kernel */
	kernel_insert<<< blocks_no, 1024 >>> (device_keys, 
											device_values, 
											numKeys, 
											hashtable);

	cudaDeviceSynchronize();

	/* increase the size of hashtable with numKeys */
	hashtable.size += numKeys;

	/* free memory */
	cudaFree(device_keys);
	cudaFree(device_values);

	return true;
}

/* GET BATCH */
int* GpuHashTable::getBatch(int* keys, int numKeys) {

	int *host_values = 0;
	int *device_keys = 0;
	int *device_values = 0;

	const int num_bytes = numKeys * sizeof(int);

	/* allocate the host_values array */
	host_values = (int *) malloc(num_bytes);

	/* allocate the device's arrays */
	cudaMalloc(&device_keys, num_bytes);
	cudaMalloc(&device_values, num_bytes);

	if(!host_values || !device_keys || !device_values) {
		/* could not allocate enough memory */
		return NULL;
	}

	/* copy from host(cpu/ram) to device(gpu/vram) */
	cudaMemcpy(device_keys, keys, num_bytes, cudaMemcpyHostToDevice);

	/*
	 *	Compute the parameters necessary to run the kernel
	 *	- the number of blocks
	 *  - the number of threads per block 
	 */

	unsigned int blocks_no = numKeys / 1024;
	
	/* deal with a possible partial final block */
	if (numKeys % 1024) {
		++blocks_no;
	}

	/* execute the kernel */
	kernel_get<<< blocks_no, 1024 >>> (device_keys,
										device_values, 
										numKeys, 
										hashtable);

	cudaDeviceSynchronize();

	/* copy from device(gpu/vram) to host(cpu/ram) */
	cudaMemcpy(host_values, device_values, num_bytes, cudaMemcpyDeviceToHost);

	return host_values;
}

/* GET LOAD FACTOR
 * num elements / hash total slots elements
 */
float GpuHashTable::loadFactor() {
	return (float)hashtable.size / (float)hashtable.capacity;
}

/*********************************************************/

#define HASH_INIT GpuHashTable GpuHashTable(1);
#define HASH_RESERVE(size) GpuHashTable.reshape(size);

#define HASH_BATCH_INSERT(keys, values, numKeys) GpuHashTable.insertBatch(keys, values, numKeys)
#define HASH_BATCH_GET(keys, numKeys) GpuHashTable.getBatch(keys, numKeys)

#define HASH_LOAD_FACTOR GpuHashTable.loadFactor()

#include "test_map.cpp"
