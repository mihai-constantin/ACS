#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

#define N 100

long f[26];
char* file;

void read_file(char* file) {
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  int i;

  FILE* in = fopen(file, "r");
  while ((read = getline(&line, &len, in)) != -1) {
    // printf("Retrieved line of length %zu:\n", read);
    // printf("%s", line);
    for (i = 0; i < read; i++) {
      if (line[i] >= 'A' && line[i] <= 'Z') {
        f[line[i] - 'A']++;
      }
    }
  }

  fclose(in);
}

void printResult() {
  int i;
  for (i = 0; i < 26; i++) {
    printf("%c %ld\n", (char)(i + 65), f[i]);
  }
}

int main()
{
  int i, tid, numThreads;
  double t1, t2;
  file = (char*) calloc(5, sizeof(char));

  t1 = omp_get_wtime();
  #pragma omp parallel default(shared) private(i, tid)
  {
    tid = omp_get_thread_num();
    numThreads = omp_get_num_threads();

    int start = tid * ceil((double)N / numThreads);
	  int end = fmin(N , (tid + 1) * ceil((double)N / numThreads));

    // printf("%d %d\n", start, end);
    for (i = start; i < end; i++) {
      #pragma omp critical
      {
        sprintf(file, "files/f%d", i);
        read_file(file);
      }
    }
  }
  t2 = omp_get_wtime();

  printResult();
  printf("Execution time %g\n", t2 - t1);

  return 0;
}