// CONSTANTIN MIHAI - 336CA
// TEMA 2 ASC

#include <cblas.h>

#include "utils.h"

double* copy(int N, double *A) {

	int i, j;

	double *B = malloc(N * N * sizeof(double));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			B[i * N + j] = A[i * N + j];
		}
	}

	return B;
}

double* add_matrix(int N, double *A, double *B) {

	int i, j;

	double *C = calloc(N * N, sizeof(double));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			C[i * N + j] = A[i * N + j] + B[i * N + j];
		}
	}
	return C;
}

double* my_solver(int N, double *A, double *B) {

	/*
		A - matrice superior triunghiulara
		B - matrice normala
		Vrem C = B * A^t + A^2 * B
	*/

	/*
		CblasRowMajor - matrice stocata pe o singura linie
		CblasRight - facem B * A^t
		CblasUpper - matrice superior triunghiulara
		CblasTrans - folosim A^t
		CblasNoTrans - folosim A, nu A^t
		CblasNonUnit - A nu e matrice unitara
	*/

	// B2 <- B2 * A^t
	double *B2 = copy(N, B);
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, B2, N);

	// A2 <- A2 * A
	double *A2 = copy(N, A);
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, A2, N);

	// B <- A2 * B
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A2, N, B, N);

	// result <- B2 + B
	double *result = add_matrix(N, B2, B);

	return result;
}

