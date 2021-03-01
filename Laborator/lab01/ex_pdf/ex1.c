#include <stdio.h>
#include <omp.h>

int main(void) {

    #pragma omp parallel
    {
        printf("Hello openmp\n");
    }
    return 0;
}
