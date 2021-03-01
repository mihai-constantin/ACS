#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {

    int th_id = 0;
    int sum = 0;

    #pragma omp parallel private(th_id) shared(sum)
    {
        th_id = omp_get_thread_num();
        printf("Thread id: %d\n", th_id);
        #pragma omp critical
        sum += th_id;
    }
    printf("[%d]: %d\n", omp_get_thread_num(), sum);

    return 0;
}