#include <stdio.h> 
#include <stdlib.h>
#include <omp.h>

int main(void) 
{
  int ID; 		/* Thread identification number*/
  int numThreads;	/* Current number of threads running */

   numThreads = omp_get_num_threads();
   printf("Outside of the pragma, the number of threads is %d\n\n", numThreads);

   #pragma omp parallel private(ID)
   {
       #pragma omp sections nowait
       {
         #pragma omp section
         {
            numThreads = omp_get_num_threads();
            printf("Inside the pragma, the number of threads is %d\n\n", numThreads);
         }
       }

        ID = omp_get_thread_num();
        printf("Hello(%d)", ID);
        printf(" world from process %d!\n\n", ID);
   }

   return 0;
}

