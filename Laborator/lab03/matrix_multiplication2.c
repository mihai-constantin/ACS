/******************************************************************************
* FILE: omp_mm.c
* DESCRIPTION:  
*   OpenMp Example - Matrix Multiply - C Version
*   Demonstrates a matrix multiply using OpenMP. Threads share row iterations
*   according to an auto chunk size.
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NRA 62                 /* number of rows in matrix A */
#define NCA 15                 /* number of columns in matrix A */
#define NCB 7                  /* number of columns in matrix B */

int main (int argc, char *argv[]) 
{
  int	tid, nthreads, i, j, k;
  double a[NRA][NCA];   /* matrix A to be multiplied */
	double b[NCA][NCB];   /* matrix B to be multiplied */
	double c[NRA][NCB];   /* result matrix C */

  double t1, t2;

  t1 = omp_get_wtime();
  /*** Spawn a parallel region explicitly scoping all variables ***/
  #pragma omp parallel shared(a, b, c, nthreads) private(tid, i, j, k)
  {
    tid = omp_get_thread_num();
    if (tid == 0) {
      nthreads = omp_get_num_threads();
      printf("Starting matrix multiple example with %d threads\n", nthreads);
      printf("Initializing matrices...\n");
    }

    #pragma omp sections nowait
    {
      /*** Initialize matrices ***/
      #pragma omp section
      for (i = 0; i < NRA; i++) {
        for (j = 0; j < NCA; j++) {
          a[i][j] = i + j;
        }
      }

      #pragma omp section
      for (i = 0; i < NCA; i++) {
        for (j = 0; j < NCB; j++) {
          b[i][j] = i * j;
        }
      }

      #pragma omp section
      for (i = 0; i < NRA; i++) {
        for (j = 0; j < NCB; j++) {
          c[i][j] = 0;
        }
      }
    }

    /*** Do matrix multiply sharing iterations on outer loop ***/
    /*** Display who does which iterations for demonstration purposes ***/
    printf("Thread %d starting matrix multiply...\n", tid);
    #pragma omp for schedule (auto)
    for (i = 0; i < NRA; i++) {
      printf("Thread=%d did row=%d\n", tid, i);
      for(j = 0; j < NCB; j++) {      
        for (k = 0; k < NCA; k++) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }   /*** End of parallel region ***/
  t2 = omp_get_wtime();

  /*** Print results ***/
  printf("******************************************************\n");
  printf("Result Matrix:\n");
  for (i = 0; i < NRA; i++) {
    for (j = 0; j < NCB; j++) {
      printf("%6.2f   ", c[i][j]);
    }
    printf("\n");
  }
  printf("******************************************************\n");
  printf("Execution time %g\n", t2 - t1);
  printf ("Done.\n");

  return 0;
}
