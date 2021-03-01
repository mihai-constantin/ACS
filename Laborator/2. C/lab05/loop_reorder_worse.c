#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 1500

const double c = 3.0;

const double epsilon = 0.0001;

double A[N][N];
double B[N][N];
double C[N][N];
double D[N][N];

int main()
{
	int i, j, k;

	double *orig_pa;
	double *pa;
	double *pb;
	double *pc;

	/* random initialization for A and B */
	srand(time(0));

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			A[i][j] = ((double)rand() / RAND_MAX) * c;
			B[i][j] = ((double)rand() / RAND_MAX) * c;
		}
	}

	clock_t t; 
    t = clock(); 

	for(k = 0; k < N; k++) {

		pb = &B[k][0];
		orig_pa = &A[0][k];

		for(j = 0; j < N; j++) {
			pc = &C[0][j];
			pa = orig_pa;

			for(i = 0; i < N; i++) {
				*pc += *pa * *pb;
  				pa += N;
      			pc += N;
			}

			pb++;
		}
	}

	t = clock() - t;

	/* in seconds */
	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	/* Verificare corectitudine */
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				D[i][j] += A[i][k] * B[k][j];
			}

			if(fabs(D[i][j] - C[i][j]) > epsilon) {
				printf("Incorrect results\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	printf("Time: %f\n", time_taken); 

	return 0;
}