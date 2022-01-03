#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 10000000
int a[N];

int main(void) {

  int i, tid, numThreads;
  for (i = 0; i < N; i++) {
    a[i] = 1;
  }

  long int sum = 0;
  double t1, t2;
  t1 = omp_get_wtime();

  #pragma omp parallel default(shared) private(i, tid)
  {
    tid = omp_get_thread_num();
    numThreads = omp_get_num_threads();

    int start = tid * ceil((double)N / numThreads);
	int end = fmin(N , (tid + 1) * ceil((double)N / numThreads));

    for (i = start; i < end; i++) {
        #pragma omp critical
        sum += a[i];
    }
  }
  
  t2 = omp_get_wtime();
  
  printf("Sum=%ld, duration=%g\n", sum, t2-t1);
  return 0;
}
