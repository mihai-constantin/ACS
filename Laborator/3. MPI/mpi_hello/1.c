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
int nums[dmax];

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
    //     printf("MASTER: Number of MPI tasks is: %d\n",numtasks);


    if(rank == 0) {
        for(int i = 0; i < dmax; i++) {
            nums[i] = i;
        }

        MPI_Send(nums, dmax, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if(rank == 1) {
        MPI_Recv(nums, dmax, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(int i = 0; i < dmax; i++) {
            printf ("Hello from task %d\n", nums[i]);

        }
    }

    
    MPI_Finalize();

    return 0;

}

