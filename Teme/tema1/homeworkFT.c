// CONSTANTIN MIHAI - 336CA

// Resurse: https://rosettacode.org/wiki/Fast_Fourier_transform#C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <pthread.h>

double PI = atan2(1, 1) * 4;

int N; // number of values
int P; // number of threads

typedef double complex cplx;

cplx* answer; // complex values buffer
cplx* buffer; // values buffer

FILE* in;
FILE* out;

void getArgs(int argc, char** argv) {
	if(argc < 4) {
		printf("Usage %s <inputValues.txt> <outputValues.txt> <numThreads>\n", argv[0]);
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
	
	buffer = (cplx*) calloc(N, sizeof(cplx));
	answer = (cplx*) calloc(N, sizeof(cplx));
	if(buffer == NULL || answer == NULL) {
		printf("calloc failed!");
		exit(1);
	}

	double x;
	for(int i = 0; i < N; i++) {
		ret = fscanf(in, "%lf", &x);
		buffer[i] = x + I * 0;
		if (ret != 1) {
    		fprintf(stdout, "Failed to read the %dth value from input file\n", i);
    		exit(1);
  		}
	}
}

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	int start = thread_id * ceil((double)N / P);
	int end = fmin(N , (thread_id + 1) * ceil((double)N / P));

	for(int k = start; k < end; k++) {
		cplx xk = 0;
		for(int n = 0; n < N; n++) {
			xk += buffer[n] * cexp(-I * 2 * PI * (double)k * (double)n / N);
		}

		answer[k] = creal(xk) + I * cimag(xk);
	}

	return NULL;
}

void print() {

	fprintf(out, "%d\n", N);
	for(int i = 0; i < N; i++) {
		fprintf(out, "%lf %lf\n", creal(answer[i]), cimag(answer[i]));
	}
}

void destroy() {
	free(buffer);
	free(answer);
}

int main(int argc, char* argv[]) {

	getArgs(argc, argv);
	init();

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

	destroy();

	// close input and output files
	fclose(in);
	fclose(out);

	return 0;
}
