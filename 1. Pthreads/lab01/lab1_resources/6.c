#include <stdio.h>
#include <math.h>
#include <pthread.h>


void* threadFunction0(void *var) {
	int thread_id = *(int*)var;
	printf("%i: HELLO\n", thread_id);
}

void* threadFunction1(void *var) {
	int thread_id = *(int*)var;
	printf("%i: BONJOUR\n", thread_id);
}

int main()
{
	// number of threads
	int P = 2;

	// create thread_id vector
	int thread_id[P];
	for(int i = 0; i < P; i++) {
		thread_id[i] = i;
	}

	pthread_t tid[P];
	pthread_create(&(tid[0]), NULL, threadFunction0, &(thread_id[0]));
	pthread_create(&(tid[1]), NULL, threadFunction1, &(thread_id[1]));

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}