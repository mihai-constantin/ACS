/*
 * This code calculates pi using the formula to calculate
 * the atan(z) which is the integral from 0 to z of 1/(1+x*x)
 * times dx.  atan(1) is 45 degrees or pi/4
 */

#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;	/* number of intervals */
double step; /* the size of the interval - dx */

int main () {	  
  int i; /* Loop control variable */
  double x; /* The current x position for function evaluation */
  double pi; /* final results */
  double sum = 0.0; /* maintains the sum of the partial results */

  step = 1.0 / (double) num_steps;

  /*
   * Calculate the integral
   */
  double t1,t2;
  t1 = omp_get_wtime();
  #pragma omp parallel for reduction(+:sum) private(x)
    for (i = 1; i <= num_steps; i++) {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
  t2 = omp_get_wtime();
  printf("Execution time %g\n", t2 - t1);

  /*
   * Multiply by dx
   */
  pi = step * sum;

  printf( "The computed value of pi is %f\n", pi);

  return 0;
}
