// minimul ce se poate obtine este 4 !!!!!
// maximul ce se poate obtine este 400

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a;

void* threadFunction(void *var) {
	for(int i = 0; i < 100; i++) {
		a += 2;
	}
}

int main(int argc, char **argv)
{
	int P = 2; // number of threads
	
	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threats
	pthread_t tid[P];
	for(int i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	printf("a = %d\n", a);

	return 0;
}
