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
    //printf ("Hello from task %d on %s!\n", rank, hostname);
    //if (rank == MASTER)
        //printf("MASTER: Number of MPI tasks is: %d\n",numtasks);
   
    if(rank == MASTER) {
        for(int i = 0; i < numtasks; i++) {
            nums[i] = i;
            MPI_Send(&nums[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    int nr_current;
    MPI_Recv(&nr_current, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int gap = 1;
    int new_nr;

    while(gap < numtasks) {
        if(rank + gap < numtasks) {
            MPI_Send(&nr_current, 1, MPI_INT, rank + gap, 0, MPI_COMM_WORLD);
        
        }

        if(rank - gap >= 0) {
            int aux;

            MPI_Recv(&aux, 1, MPI_INT, rank - gap, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            new_nr = nr_current + aux;
        }

        nr_current = new_nr;
        gap *= 2;
    }

    if(rank == numtasks - 1) {
        printf("Suma finala: %d\n", nr_current);
    }


    MPI_Finalize();


    return 0;
}

