// CONSTANTIN MIHAI - 336CA

// Resurse
// https://rosettacode.org/wiki/Fast_Fourier_transform#C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <pthread.h>

double PI = atan2(1, 1) * 4;

FILE* in;
FILE* out;

int N; // number of values
double* buffer; // values buffer
int P; // number of threads

typedef double complex cplx;

void getArgs(int argc, char** argv) {
	if(argc < 4) {
		printf("Not enough paramters: ./homeworkFT inputValues.txt outputValues.txt numThreads\n");
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if (in == NULL || out == NULL) {
    	fprintf(stdout, "Failed to open at least one file.\n");
    	exit(1);
  	} 
	
	P = atoi(argv[3]);
}

void init() {

	int ret = fscanf(in, "%d", &N);
	if (ret != 1) {
    	fprintf(stdout, "Failed to read N.\n");
    	exit(1);
  	}
	
	buffer = (double*) malloc(N * sizeof(double));
	for(int i = 0; i < N; i++) {
		ret = fscanf(in, "%lf", &buffer[i]);
		if (ret != 1) {
    		fprintf(stdout, "Failed to read the %dth value from input file\n", i);
    		exit(1);
  		}
	}
}

void ft() {

	fprintf(out, "%d\n", N);

	for(double k = 0; k < N; k++) {
		// calculate X_k
		cplx xk = 0;
		for(int n = 0; n < N; n++) {
			xk += buffer[n] * cexp(-I * 2 * PI * k * (double)n / N);
		}

		fprintf(out, "%0.6lf %.6lf\n", creal(xk), cimag(xk));
	}
}

int main(int argc, char* argv[]) {

	getArgs(argc, argv);
	init();
	ft();

	return 0;
}
