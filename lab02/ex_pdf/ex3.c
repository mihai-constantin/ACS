#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <omp.h>

long f[26];

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
  int i;
  double t1, t2;
  char* file = (char*) malloc(5 * sizeof(char));

  t1 = omp_get_wtime();
  for (i = 0; i < 100; i++) {
    sprintf(file, "files/f%d", i);
    read_file(file);
  }
  t2 = omp_get_wtime();

  printResult();
  printf("Execution time %g\n", t2 - t1);

  return 0;
}