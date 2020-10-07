#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
    int a = 2;
    
    #pragma omp parallel private(a)
    {
        int numThreads = omp_get_num_threads();
        a = 3;
        printf("Hello from %d/%d thread\n", omp_get_thread_num(), numThreads);
    }

    printf("[%d]: %d\n", omp_get_thread_num(), a);

    return 0;
}