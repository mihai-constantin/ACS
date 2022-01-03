#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1500

const double c = 3.0; 

double A[N][N];
double B[N][N];
double C[N][N];

int main()
{
	int i, j, k;

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

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	t = clock() - t;

	/* in seconds */
	double time_taken = ((double)t)/CLOCKS_PER_SEC;

	printf("Time: %f\n", time_taken); 

	return 0;
}