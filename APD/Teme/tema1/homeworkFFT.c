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

pthread_barrier_t barrier;

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

void fft(cplx* buf, cplx* output, int step)
{
	if (step < N) {

		if((2 * step) < N) {
			fft(output, buf, step * 2); 
			fft(output + step, buf + step, step * 2);
		}
 
		for (int i = 0; i < N; i += 2 * step) {
			cplx t = cexp(-I * PI * i / N) * output[i + step];
			buf[i / 2]     = output[i] + t;
			buf[(i + N)/2] = output[i] - t;
		}
	}
}

void* threadFunction1(void *var)
{
	fft(buffer, answer, 1);
	return NULL;
}

void* threadFunction2(void *var)
{
	int thread_id = *(int*)var;

	// left tree - thread 0
	if(thread_id == 0) {
		fft(answer, buffer, 2); 
	}

	// right tree - thread 1
	if(thread_id == 1) {
		fft(answer + 1, buffer + 1, 2);
	}

	// barrier - wait results from both trees
	pthread_barrier_wait(&barrier);

	// create final result
	if(thread_id == 0) {
		for (int i = 0; i < N; i += 2 * 1) {
			cplx t = cexp(-I * PI * i / N) * answer[i + 1];
			buffer[i / 2]     = answer[i] + t;
			buffer[(i + N)/2] = answer[i] - t;
		}
	}
	
	return NULL;
}

void* threadFunction4(void *var)
{
	int thread_id = *(int*)var;

	if(thread_id == 0) {
		fft(buffer, answer, 4);
	}
	
	if(thread_id == 1) { 
		fft(buffer + 2, answer + 2, 4);
	}

	pthread_barrier_wait(&barrier);

	if(thread_id == 2) {
		fft(buffer + 1, answer + 1, 4);
	}

	if(thread_id == 3) {
		fft(buffer + 3, answer + 3, 4);
	}

	pthread_barrier_wait(&barrier);

	// combine left and right trees
	if(thread_id == 0) {
		for (int i = 0; i < N; i += 2 * 2) {
			cplx t = cexp(-I * PI * i / N) * buffer[i + 2];
			answer[i / 2]     = buffer[i] + t;
			answer[(i + N)/2] = buffer[i] - t;
		}
	}

	if(thread_id == 1) {
		cplx* buffer1 = buffer + 1;
		cplx* answer1 = answer + 1;

		for (int i = 0; i < N; i += 2 * 2) {
			cplx t = cexp(-I * PI * i / N) * buffer1[i + 2];
			answer1[i / 2]     = buffer1[i] + t;
			answer1[(i + N)/2] = buffer1[i] - t;
		}
	}

	pthread_barrier_wait(&barrier);

	// create final result
	for (int i = 0; i < N; i += 2 * 1) {
		cplx t = cexp(-I * PI * i / N) * answer[i + 1];
		buffer[i / 2]     = answer[i] + t;
		buffer[(i + N)/2] = answer[i] - t;
	}

	return NULL;
}

void print() {

	fprintf(out, "%d\n", N);
	for(int i = 0; i < N; i++) {
		fprintf(out, "%lf %lf\n", creal(buffer[i]), cimag(buffer[i]));
	}
}

void destroy() {
	free(buffer);
	free(answer);
}

int main(int argc, char * argv[]) {

	getArgs(argc, argv);
	init();

	// initialize barrier
	pthread_barrier_init(&barrier , NULL, P);

	// FFT - initialize answer vector
	for (int i = 0; i < N; i++) {
		answer[i] = buffer[i];
 	}

	// create thread_id vector
	int thread_id[P];
	for(int i = 0;i < P; i++)
		thread_id[i] = i;

	// create P threads
	pthread_t tid[P];
	for(int i = 0; i < P; i++) {
		switch(P) {
			case 1:
					pthread_create(&(tid[i]), NULL, threadFunction1, &(thread_id[i]));
					break;
			case 2:
					pthread_create(&(tid[i]), NULL, threadFunction2, &(thread_id[i]));
					break;
			case 4:
					pthread_create(&(tid[i]), NULL, threadFunction4, &(thread_id[i]));
					break;

			default:
					break;
		}
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	// destroy barrier
	if(P != 1) {
		pthread_barrier_destroy(&barrier);
	}

	destroy();

	// close input and output files
	fclose(in);
	fclose(out);

	return 0;
}
