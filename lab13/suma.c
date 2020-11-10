#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc , char **argv)
{
	double *Array, *Check, serial_sum, sum;
	int array_size, i, num_threads;

	/* Checking for command line arguments */
    if( argc != 3 ) {
        printf("Invalid number of arguments!\n");
		printf("Running example: ./suma <num_threads> <array-size>\n");
        exit(-1);
    }

    num_threads = atoi(argv[1]);

    array_size = atoi(argv[2]);
    /* Array Size should be positive integer */
	if (array_size <= 0) {
		printf("Array Size Should Be Of Positive Value ");
		exit(1);
	}

    printf("Threads : %d\n", num_threads);
    printf("Array Size : %d\n", array_size);

	/* Dynamic Memory Allocation */
	Array = (double *) malloc(sizeof(double) * array_size);
	Check = (double *) malloc(sizeof(double) * array_size);

	/* Array Elements Initialization */
	for (i = 0; i < array_size; i++) {
		Array[i] = i;
		Check[i] = Array[i];
	}

	sum = 0.0;

    /* set the number of threads */
	omp_set_num_threads(num_threads);

	/* OpenMP Parallel For Directive And Critical Section */
	#pragma omp parallel for
	for (i = 0; i < array_size; i++) {
		#pragma omp critical
		sum = sum + Array[i];
    } /* End of parallel region */

	serial_sum = 0.0;
	/* Serail Calculation */
	for (i = 0; i < array_size; i++) {
		serial_sum = serial_sum + Check[i];
	}

	if (serial_sum == sum) {
		printf("The Serial And Parallel Sums Are Equal\n");
	}
	else {
		printf("The Serial And Parallel Sums Are UnEqual\n");
		exit(1);
	}

	/* Freeing Memory */
	free(Check);
	free(Array);

	printf("The SumOfElements Of The Array Using OpenMP Directives Is %lf\n", sum);
	printf("The SumOfElements Of The Array By Serial Calculation Is %lf\n", serial_sum);

    return 0;
}
