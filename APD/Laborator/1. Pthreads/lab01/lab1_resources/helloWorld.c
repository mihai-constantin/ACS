#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

void* threadFunction(void *var) {
	int thread_id = *(int*)var;
	printf("Hello world from thread %i\n", thread_id);
}

// exercise 4
void* threadFunction2(void *var) {
	int thread_id = *(int*)var;
	for(int i = 1; i <= 100; i++) {
		printf("%d: Hello World from thread %i\n", i, thread_id);
	}
}

int main(int argc, char **argv)
{
	// exercise 2
	long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);

	// exercise 3
	// change the number of threads to be equal to number of cores
	// available on this computer
	int P = number_of_processors;
	
	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threats
	pthread_t tid[P];
	for(int i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction2, &(thread_id[i]));
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("nproc: %ld\n", number_of_processors);

	return 0;
}
