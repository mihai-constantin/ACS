/******************************************************************************
* FILE: omp_workshare2.c
* DESCRIPTION:
*   OpenMP Example - Sections Work-sharing - C Version
*   In this example, the OpenMP SECTION directive is used to assign
*   different array operations to each thread that executes a SECTION. 
* AUTHOR: Blaise Barney  5/99
* LAST REVISED: 07/16/07
******************************************************************************/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100000000
float a[N], b[N], c[N], d[N];

int main (int argc, char *argv[]) 
{
    int i;
    double t1,t2;
    /* Some initializations */
    for (i=0; i<N; i++) {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
        c[i] = d[i] = 0.0;
    }
    t1 = omp_get_wtime();
    for (i=0; i<N; i++)
    {
        c[i] = sin(a[i] + b[i]);
    }

    for (i=0; i<N; i++)
    {
        d[i] = sqrt(a[i] * b[i]);
    }
    t2 = omp_get_wtime();

    printf("Duration %g\n",t2-t1);

    return 0;
}
