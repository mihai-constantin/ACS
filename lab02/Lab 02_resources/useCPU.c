#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define dmax 1000000

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	printf("Hello world from thread %i\n", thread_id);

	for(int i = 0; i < dmax; i++) {
		for(int j = 0; j < dmax; j++) {
			int ans = sqrt(i * j);
		}
	}
}

int main(int argc, char **argv)
{
	int P = 4;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
