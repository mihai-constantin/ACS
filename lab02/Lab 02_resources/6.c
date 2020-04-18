#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a = 0;
void* threadFunction(void *var)
{
	a = a + 2;
	printf("%d\n", a);
}

int main(int argc, char **argv)
{
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

	return 0;
}
