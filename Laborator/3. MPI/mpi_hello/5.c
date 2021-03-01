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
    
    int number;

    if(rank == 0) {
        number = 0;
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&number, 1, MPI_INT, numtasks - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else {
        MPI_Recv(&number, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        number += 2;
        if(rank + 1 != numtasks - 1) 
            MPI_Send(&number, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        else
            MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    printf("number = %d\n", number);


    MPI_Finalize();

    return 0;

}

