#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int** matrix;
int* aux;
int n, m;

void allocate_matrix() {

	matrix = (int**) malloc(n * sizeof(int*));
	for(int i = 0; i < n; i++) {
		matrix[i] = (int*) malloc(m * sizeof(int));
	}

}

void init_matrix() {
	srand(time(0)); 
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			matrix[i][j] = rand() % 10;
		}
	}
}

void print_matrix() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	printf("----------------------------\n");
}

int cmp(const void* a, const void* b) {
	return ( *(int*)a - *(int*)b );
}

void sort_rows() {
	for(int i = 0; i < n; i++) {
		qsort(matrix[i], m, sizeof(int), cmp);
	}
}

void copy_column(int j) {
	for(int i = 0; i < n; i++) {
		aux[i] = matrix[i][j];
	}
}

void sort_column() {
	qsort(aux, n, sizeof(int), cmp);
}

void write_back(int j) {
	for(int i = 0; i < n; i++) {
		matrix[i][j] = aux[i];
	}
}

void sort_colums() {
	aux = (int*) malloc(n * sizeof(int));
	for(int j = 0; j < m; j++) {
		// sort j_th column
		copy_column(j);
		sort_column();
		write_back(j);
	}
}

int main()
{
	printf("n = ");
	scanf("%d", &n);
	printf("m = ");
	scanf("%d", &m);

	allocate_matrix();
	init_matrix();
	print_matrix();

	sort_rows();
	print_matrix();

	sort_colums();
	print_matrix();

	return 0;
}