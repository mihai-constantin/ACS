#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int P;
int** a;
int** b;
int** c;

pthread_mutex_t mutex;

void* threadFunction(void *args)
{
	// TODO: Implement parallel multiply of matrices: C = A * B
	// using P threads by splitting the inner loop.

	int thread_id = *(int*)args;

	int start = thread_id * ceil((double)N / P);
	int end = fmin(N, (thread_id + 1) * ceil((double) N / P));

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			for(int k = start; k < end; k++) {
				pthread_mutex_lock(&mutex);
				c[i][j] += a[i][k] * b[k][j];
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	

	return NULL;
}

void getArgs(int argc, char **argv)
{
	if(argc < 5) {
		printf("Not enough paramters: ./program N NReps printLevel P\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
	P = atoi(argv[4]);
}

void init()
{
	a = malloc(sizeof(int *) * N);
	b = malloc(sizeof(int *) * N);
	c = malloc(sizeof(int *) * N);
	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for(i = 0; i < N; i++) {
		a[i] = malloc(sizeof(int) * N);
		b[i] = malloc(sizeof(int) * N);
		c[i] = malloc(sizeof(int) * N);
		if(a[i] == NULL || b[i] == NULL || c[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			c[i][j] = 0;
			if(i <= j) {
				a[i][j] = 1;
				b[i][j] = 1;
			}
			else {
				a[i][j] = 0;
				b[i][j] = 0;
			}
		}
	}
}

void printAll()
{
	int i, j;

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i ", b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i ", c[i][j]);
		}
		printf("\n");
	}
}

void printPartial()
{
	printAll();
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

int main(int argc, char *argv[])
{
	int i, j, k;
	getArgs(argc, argv);
	init();

	pthread_mutex_init(&mutex, NULL);

	// create thread_id vector
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threads
	pthread_t tid[P];
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	pthread_mutex_destroy(&mutex);

	return 0;
}
