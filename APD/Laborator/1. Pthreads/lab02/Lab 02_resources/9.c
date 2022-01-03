// se afiseaza 1 2 tot timpul

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_barrier_t barrier;

void* threadFunction0(void *var)
{
	printf("1\n");
	pthread_barrier_wait(&barrier);
}

void* threadFunction1(void *var)
{
	pthread_barrier_wait(&barrier);
	printf("2\n");
}

int main(int argc, char **argv)
{
	int P = 2; // number of threads

	// create barrier
	pthread_barrier_init(&barrier, NULL, P);

	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create threats
	pthread_t tid[P];
	pthread_create(&(tid[0]), NULL, threadFunction0, &(thread_id[0]));
	pthread_create(&(tid[1]), NULL, threadFunction1, &(thread_id[1]));

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	pthread_barrier_destroy(&barrier);

	return 0;
}
