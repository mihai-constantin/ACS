#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 0.001

int main(int argc, char *argv[]) {
  int i;

  if (argc < 2) {
    fprintf(stdout, "Usage %s <file1> <file2>\n", argv[0]);
    exit(1);
  }

  FILE *fp1 = fopen(argv[1], "rt");
  FILE *fp2 = fopen(argv[2], "rt");
  if (fp1 == NULL || fp2 == NULL) {
    fprintf(stdout, "Failed to open at least one file.\n");
    exit(1);
  }

  int ret, ret1, ret2;
  int N1, N2;
  ret1 = fscanf(fp1, "%d", &N1);
  ret2 = fscanf(fp2, "%d", &N2);

  if (ret1 != ret2 || ret1 != 1) {
    fprintf(stdout, "Failed to read N from one of the files.\n");
    exit(1);
  }

  if (N1 != N2) {
    printf("The values for N are not equal\n");
    exit(1);
  }

  double auxRe1, auxRe2, auxImg1, auxImg2;
  for (i = 0; i < N1; i++) {
    ret = fscanf(fp1, "%lf%lf", &auxRe1, &auxImg1);
    if (ret != 2) {
      fprintf(stdout, "Failed to read the %dth pair from the first file.\n", i);
      exit(1);
    }

    ret = fscanf(fp2, "%lf%lf", &auxRe2, &auxImg2);
    if (ret != 2) {
      fprintf(stdout, "Failed to read the %dth pair from the 2nd file\n", i);
      exit(1);
    }

    if (fabs(auxRe1 - auxRe2) > EPS || fabs(auxImg1 - auxImg2) > EPS) {
      printf("Found unmatching values on the %dth pair\n", i);
      printf("(%g, %g) \n", auxRe1, auxImg1);
      printf("(%g, %g) \n", auxRe2, auxImg2);
      printf("not equal\n");
      exit(1);
    }
  }

  fclose(fp1);
  fclose(fp2);
  printf("equal\n");
  return 0;
}
