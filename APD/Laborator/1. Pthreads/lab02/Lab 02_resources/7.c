// se afiseaza 2 4 tot timpul

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_mutex_t mutex;

int a = 0;
void* threadFunction(void *var)
{
	pthread_mutex_lock(&mutex);
	a = a + 2;
	printf("%d\n", a);
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv)
{
	// init mutex
	pthread_mutex_init(&mutex, NULL);

	int P = 2;
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

	pthread_mutex_destroy(&mutex);

	return 0;
}
