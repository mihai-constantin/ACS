#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a;

pthread_barrier_t barrier;

void* threadFunction0(void *var) {
	pthread_barrier_wait(&barrier);
	a = 5;
	 //printf("a doua oara\n");
	pthread_barrier_wait(&barrier);
	
	a += 7;
	 //printf("a treia oara\n");


}

void* threadFunction1(void *var) {
	a = 3;
	 //printf("prima data\n");
	pthread_barrier_wait(&barrier);	
	pthread_barrier_wait(&barrier);	
	a += 2;
	 //printf("a patra oara\n");
}

int main(int argc, char **argv)
{
	int P = 2; // number of threads

	pthread_barrier_init(&barrier, NULL, P); // initializare bariera
	
	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threats
	pthread_t tid[P];
	pthread_create(&(tid[0]), NULL, threadFunction0, &(thread_id[0]));
	pthread_create(&(tid[1]), NULL, threadFunction1, &(thread_id[1]));

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("a = %d\n", a);

	return 0;
}
