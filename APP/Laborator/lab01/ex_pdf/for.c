#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {

    int i, x[100];

    #pragma omp parallel private(i) shared(x)
    {
        #pragma omp for
        for (i = 0; i < 100; i++) {
            x[i] = i;
        }
    }

    long int sum = 0;

    #pragma omp for
    for (i = 0; i < 100; i++) {
        sum += x[i];
    }

    printf("Thread id: [%d]\n", omp_get_thread_num());
    for (i = 0; i < 100; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");

    #pragma omp parallel
    {
        printf("[%d]: sum = %ld\n", omp_get_thread_num(), sum);
    }

    return 0;
}