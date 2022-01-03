#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N, P;
int* a;
int* s;

void getArgs(int argc, char **argv) {
	if(argc < 3) {
		printf("Not enough parameters: %s <number_of_threads> <length_vector>\n", argv[0]);
		exit(1);
	}
  P = atoi(argv[1]);
	N = atoi(argv[2]);
}

void init() {
	a = malloc(sizeof(int) * N);
	s = malloc(sizeof(int) * P);
	if(a == NULL || s == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	for(int i = 0; i < N; i++) {
		a[i] = i;
	}
}

void* threadFunction(void *var) {
	int thread_id = *(int*)var;

	int start = thread_id * ceil((double)N / P);
	int end = fmin(N , (thread_id + 1) * ceil((double)N / P));

  for(int i = start; i < end; i++)
    s[thread_id] += a[i];
  
  return NULL;
}

void print() {
	int i;
	
	printf("a: ");
	for(i = 0; i < N; i++) {
		printf("%i ", a[i]);
  }
	printf("\n");

  printf("s: ");
	for(i = 0; i < P; i++) {
		printf("%i ", s[i]);
  }
	printf("\n");
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);
	init();

	// create thread_id vector
	int thread_id[P];
	for(int i = 0; i < P; i++) {
		thread_id[i] = i;
  }

	// create P thread
	pthread_t tid[P];
	for(int i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

  int serial_sum = 0;
	/* Serail Calculation */
	for (int i = 0; i < N; i++) {
		serial_sum = serial_sum + a[i];
	}

  int total_sum = 0;
  for (int i = 0; i < P; i++) {
    total_sum += s[i];
  }

	// print();

  if (serial_sum == total_sum) {
		printf("The Serial And Parallel Sums Are Equal\n");
	}
	else {
		printf("The Serial And Parallel Sums Are UnEqual\n");
		exit(1);
	}

  free(a);
	free(s);

  printf("The SumOfElements Of The Array Using Pthreads Is %d\n", total_sum);
	printf("The SumOfElements Of The Array By Serial Calculation Is %d\n", serial_sum);

	return 0;
}
