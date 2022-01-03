#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int** matrix;
int* row;
int* column;

int N, M;
int P;

pthread_barrier_t barrier;
pthread_mutex_t mutex;

int cmp_asc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int cmp_desc(const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N M P\n");
		exit(1);
	}

	N = atoi(argv[1]);
	M = atoi(argv[2]);
	P = atoi(argv[3]); 

	row = (int*) malloc(M * sizeof(int));
	if(row == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	column = (int*) malloc(N * sizeof(int));
	if(column == NULL) {
		printf("malloc failed!");
		exit(1);
	}
}

void init_matrix() {
	matrix = (int**)malloc(sizeof(int*) * N);
	if(matrix == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	for(int i = 0; i < N; i++) {
		matrix[i] = (int*)malloc(sizeof(int) * M);
		if(matrix[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			matrix[i][j] = rand() % 10;
		}
	}
}

void sortRow(int lin, int asc) {

	for(int j = 0; j < M; j++) {
		row[j] = matrix[lin][j];
	}

	if(asc) {
		qsort(row, M, sizeof(int), cmp_asc);
	} else {
		qsort(row, M, sizeof(int), cmp_desc);
	}

	// copiem in matrice vectorul sortat
	for(int j = 0; j < M; j++) {
		matrix[lin][j] = row[j];
	}
}

void sortColumn(int col) {

	for(int i = 0; i < N; i++) {
		column[i] = matrix[i][col];
	}

	qsort(column, N, sizeof(int), cmp_asc);

	// copiem in matrice vectorul sortat
	for(int i = 0; i < N; i++) {
		matrix[i][col] = column[i];
	}
}

void* threadFunction(void* var)
{
	int thread_id = *(int*)var;

	int start_lin = thread_id * ceil((double)N / P);
	int end_lin = fmin(N, (thread_id + 1) * ceil((double) N / P));

	int start_col = thread_id * ceil((double)M / P);
	int end_col = fmin(N, (thread_id + 1) * ceil((double) M / P));

	int steps = ceil(log2((double)N)) + 1;

	for(int k = 0; k < steps; k++) {

		for(int i = start_lin; i < end_lin; i++) {
			if(i & 1) {
				pthread_mutex_lock(&mutex);
				sortRow(i, 0);
				pthread_mutex_unlock(&mutex);
			} else {
				pthread_mutex_lock(&mutex);
				sortRow(i, 1);
				pthread_mutex_unlock(&mutex);
			}
		}

		pthread_barrier_wait(&barrier);

		for(int j = start_col; j < end_col; j++) {
			pthread_mutex_lock(&mutex);
			sortColumn(j);
			pthread_mutex_unlock(&mutex);
		}	

		pthread_barrier_wait(&barrier);
	}

	return NULL;
}

void print() {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char* argv[]) {

	getArgs(argc, argv);
	init_matrix();

	// initialize mutex & barrier
	pthread_mutex_init(&mutex, NULL);
	pthread_barrier_init(&barrier, NULL, P);

	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threads
	pthread_t tid[P];
	for(int i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	// destroy mutex & barrier
    pthread_mutex_destroy(&mutex);
	pthread_barrier_destroy(&barrier);

	return 0;
}

