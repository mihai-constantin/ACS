// exercise 4

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int* a;
int* b;
int* c;

int P = 4; // number of threads

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N NReps printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
}

void init()
{
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);
	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i;
	for(i = 0; i < N; i++) {
		a[i] = i%500;
		b[i] = i%500;
	}
}

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	int start = thread_id * ceil((double)N / P);
	int end = fmin(N , (thread_id + 1) * ceil((double)N / P));

	// printf("thread %i: %d %d\n", thread_id, start, end);

	for(int j = 0; j < NReps; j++)
		for(int i = start; i < end; i++)
			c[i] = a[i] + b[i];
}

void print() {
	int i;
	
	printf("a: ");
	for(i = 0; i < N; i++)
		printf("%i ", a[i]);
	printf("\n");

	printf("b: ");
	for(i = 0; i < N; i++)
		printf("%i ", b[i]);
	printf("\n");

	printf("c: ");
	for(i = 0; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);
	init(); // init vectors

	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P thread
	pthread_t tid[P];
	for(int i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	// print();

	return 0;
}
