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
#define  MASTER 0

#define dmam 100

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
    	for(int i = 0; i < dmax; i++) {
    		nums[i] = i;
    	}

    	for(int i = 1; i < dmax; i++) {
        	MPI_Send(nums[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    	}
    }
    
   	int nr;
   	MPI_Recv(&nr, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


   	int gap = 1;
   	while()


    MPI_Finalize();

    return 0;

}

