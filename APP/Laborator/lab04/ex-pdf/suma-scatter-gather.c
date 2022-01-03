/******************************************************************************
* FILE: mpi_hello.c
* DESCRIPTION:
*   MPI tutorial example code: Simple hello world program
* AUTHOR: Blaise Barney
* LAST REVISED: 03/05/10
******************************************************************************/
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define  MASTER		0

#define dmax 100
#define sc 4

int main (int argc, char *argv[])
{
    int   numtasks, rank, len, sum = 0, mysum, partial_sum, i, source, tagsum = 1;
    MPI_Status status;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Get_processor_name(hostname, &len);
    // printf ("Hello from task %d on %s!\n", rank, hostname);
    // if (rank == MASTER)
        // printf("MASTER: Number of MPI tasks is: %d\n",numtasks);
    
    int nums[dmax];
    int nums2[dmax / numtasks];

    if(rank == MASTER) {
        for(i = 0; i < dmax; i++) {
            nums[i] = i;
        }
    }

    // scatter vector
    MPI_Scatter(nums, dmax / sc, MPI_INT, nums2, dmax / sc, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (rank == MASTER) {
        for(i = 0; i < dmax / numtasks; i++) {
            sum += nums2[i];
        }
        for (i = 1; i < numtasks; i++) {
            source = i;
            MPI_Recv(&partial_sum, 1, MPI_DOUBLE, source, tagsum, MPI_COMM_WORLD, &status);
            sum += partial_sum;
        }

        printf("Final sum: %d\n", sum);
    } else {
        mysum = 0;
        for(i = 0; i < dmax / numtasks; i++) {
            mysum += nums2[i];
        }
        MPI_Send(&mysum, 1, MPI_INT, MASTER, tagsum, MPI_COMM_WORLD);
    }

    // getter vector
    MPI_Gather(nums2, dmax / sc, MPI_INT, nums, dmax / sc, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Finalize();

    return 0;

}
