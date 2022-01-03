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
    int   numtasks, rank, len;
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

    if(rank == 0) {
        for(int i = 0; i < dmax; i++) {
            nums[i] = i;
        }
    }

    // scatter vector
    MPI_Scatter(nums, dmax / sc, MPI_INT, nums2, dmax / sc, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < dmax / numtasks; i++) {
        nums2[i] += 42;
    }

    // getter vector
    MPI_Gather(nums2, dmax / sc, MPI_INT, nums, dmax / sc, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){

        for(int i = 0; i < dmax; i++) {
            printf ("%d ", nums[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;

}

