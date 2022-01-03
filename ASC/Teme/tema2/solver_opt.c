// CONSTANTIN MIHAI - 336CA
// TEMA 2 ASC

#include "utils.h"

/*
	A - matrice normala
	B - matrice superior triunghiulara
	C = A * B^t
*/
double* matrix_multiplication1(int N, double *A, double *B) {

	register double *orig_pa;
	register double *pa;
	register double *pb;
	register double suma;

	register int i;
	register int j;
	register int k;

	double *C = malloc(N * N * sizeof(double));

	for(i = 0; i < N; i++) {
  		orig_pa = A + i * N;

  		for(j = 0; j < N; j++) {
    		pa = orig_pa + j;
    		pb = B + j * (N + 1);
    		suma = 0;

    		for(k = j; k < N; k++) {
      			suma += *pa * *pb;
      			pa++;
      			pb++;
    		}

    		C[i * N + j] = suma;
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

	register double *orig_pa;
	register double *pa;
	register double *pb;
	register double suma;

	register int i;
	register int j;
	register int k;

	double *C = malloc(N * N * sizeof(double));

	for(i = 0; i < N; i++) {
  		orig_pa = A + i * N;

  		for(j = 0; j < N; j++) {
    		pa = orig_pa + i;
    		pb = B + i * N + j;
    		suma = 0;

    		for(k = i; k < N; k++) {
      			suma += *pa * *pb;
      			pa++;
      			pb += N;
    		}

    		C[i * N + j] = D[i * N + j] + suma;
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

	register double *pa;
	register double *pb;
	register double *orig_pa;
	register double suma;

	register int i;
	register int j;
	register int k;

	double *C = malloc(N * N * sizeof(double));

	for(i = 0; i < N; i++) {
  		orig_pa = A + i * N;

  		for(j = i; j < N; j++) {
    		pa = orig_pa + i;
    		pb = B + i * N + j;
    		suma = 0;

    		for(k = i; k <= j; k++) {
      			suma += *pa * *pb;
      			pa++;
      			pb += N;
    		}

    		C[i * N + j] = suma;
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

