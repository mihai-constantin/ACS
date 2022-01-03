#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int** matrix;
int* row;
int* column;

int N, M;

void print() {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int cmp_asc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int cmp_desc(const void * a, const void * b) {
   return ( *(int*)b - *(int*)a );
}

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program N M\n");
		exit(1);
	}

	N = atoi(argv[1]);
	M = atoi(argv[2]);

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
	matrix = (int**)malloc(sizeof(int*) * N * M);
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

	srand(time(0));

	// for(int i = 0; i < N; i++) {
	// 	for(int j = 0; j < M; j++) {
	// 		matrix[i][j] = rand() % 10;
	// 	}
	// }

	matrix[0][0] = 9;
	matrix[0][1] = 6;
	matrix[0][2] = 9; 
	matrix[0][3] = 4; 
	
	matrix[1][0] = 2; 
	matrix[1][1] = 7; 
	matrix[1][2] = 6; 
	matrix[1][3] = 5;

	matrix[2][0] = 9; 
	matrix[2][1] = 3; 
	matrix[2][2] = 6; 
	matrix[2][3] = 2;

	matrix[3][0] = 5; 
	matrix[3][1] = 4; 
	matrix[3][2] = 1; 
	matrix[3][3] = 5; 

	print();
	printf("\n");
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

void shareSort()
{
	for(int i = 0; i < N; i++) {
		if(i & 1) {
			sortRow(i, 0);
		} else {
			sortRow(i, 1);
		}
	}

	for(int j = 0; j < M; j++) {
		sortColumn(j);
	}
}

int main(int argc, char* argv[]) {

	getArgs(argc, argv);
	init_matrix();

	for(int i = 0; i < 3; i++) {
		shareSort();
	}

	print();

	return 0;
}

