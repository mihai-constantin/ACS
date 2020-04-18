#include <stdio.h>
#include <stdlib.h>

// ./inputGenerator N fileName randomSeed
// ./inputGenerator 4096 in.data 42

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stdout, "Usage: %s <N> <fileName> <randomSeed>\n", argv[0]);
    exit(1);
  }

  int N = atoi(argv[1]);
  FILE *fp = fopen(argv[2], "wt");
  if (fp == NULL) {
    fprintf(stdout, "Failed to open the file\n.");
    exit(1);
  }

  srand(atoi(argv[3]));

  fprintf(fp, "%d\n", N);
  for (int i = 0; i < N; i++) {
    fprintf(fp, "%f\n", (double)(rand() % 1000));
  }
  fclose(fp);
  return 0;
}
