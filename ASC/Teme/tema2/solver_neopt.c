// CONSTANTIN MIHAI - 336CA
// TEMA 2 ASC

#include "utils.h"

/*
	A - matrice normala
	B - matrice superior triunghiulara
	C = A * B^t
*/
double* matrix_multiplication1(int N, double *A, double *B) {

	int i, j, k;

	double *C = calloc(N * N, sizeof(double));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = j; k < N; k++) {
				C[i * N + j] += A[i * N + k] * B[j * N + k]; 
			}
		}
	}

	return C;
}

/*
	A - matrice superior triunghiulara
	B - matrice normala
	C = A * B + D
*/
double* matrix_multiplication2(int N, double *A, double *B, double *D) {

	int i, j, k;
	
	double *C = calloc(N * N, sizeof(double));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = i; k < N; k++) {
				C[i * N + j] += A[i * N + k] * B[k * N + j]; 
			}
			C[i * N + j] += D[i * N + j];
		}
	}
	
	return C;
}

/*
	A - matrice superior triunghiulara
	B - matrice superior triunghiulara
	C = A * B

*/
double* matrix_multiplication3(int N, double *A, double *B) {

	int i, j, k;
	
	double *C = calloc(N * N, sizeof(double));
	for (i = 0; i < N; i++) {
		for (j = i; j < N; j++) {
			for (k = i; k <= j; k++) {
				C[i * N + j] += A[i * N + k] * B[k * N + j]; 
			}
		}
	}

	return C;
}

double* my_solver(int N, double *A, double* B) {

	double *C;

	/*
		A - matrice superior triunghiulara
		B - matrice normala
		Vrem C = B * A^t + A^2 * B
	*/

	C = matrix_multiplication2(N, matrix_multiplication3(N, A, A), B, 
			matrix_multiplication1(N, B, A));

	return C;
}
