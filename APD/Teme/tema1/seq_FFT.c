// CONSTANTIN MIHAI - 336CA

// Resurse de inspiratie in rezolvarea temei
// https://rosettacode.org/wiki/Fast_Fourier_transform#C

// Varianta normala, neparalelizata

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
	
	buffer = (cplx*) malloc(N * sizeof(cplx));
	answer = (cplx*) malloc(N * sizeof(cplx));
	if(buffer == NULL || answer == NULL) {
		printf("malloc failed!");
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

void _fft(cplx* buf, cplx* output, int step)
{
	if (step < N) {
		_fft(output, buf, step * 2);
		_fft(output + step, buf + step, step * 2);
 
		for (int i = 0; i < N; i += 2 * step) {
			cplx t = cexp(-I * PI * i / N) * output[i + step];
			buf[i / 2]     = output[i] + t;
			buf[(i + N)/2] = output[i] - t;
		}
	}
}
 
void fft()
{
	for (int i = 0; i < N; i++) {
		answer[i] = buffer[i];
 	}

	_fft(buffer, answer, 1);
}

void print() {

	fprintf(out, "%d\n", N);
	for(int i = 0; i < N; i++) {
		fprintf(out, "%lf %lf\n", creal(buffer[i]), cimag(buffer[i]));
	}
}

int main(int argc, char * argv[]) {

	getArgs(argc, argv);
	init();
	fft();

	print();

	return 0;
}
