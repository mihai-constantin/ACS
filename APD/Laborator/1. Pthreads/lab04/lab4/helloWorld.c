#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	printf("Hello world from thread %i\n", thread_id);
}

int main(int argc, char **argv)
{
	int P = 4; // number of threads

	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threads
	pthread_t tid[P];
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
