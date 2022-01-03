#include <stdio.h>
#include <omp.h>

int main(void) {

    #pragma omp parallel
    {
        int tcount = omp_get_num_threads();
        int tid = omp_get_thread_num();
        printf("Hello openmp from thread = %d/%d\n", tid, tcount);
    }
    return 0;
}
