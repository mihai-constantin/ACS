#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define  ARRAYSIZE	21
#define  MASTER		0

double data[ARRAYSIZE];

double update(int myoffset, int chunk, int myid) {
    int i;
    double mysum = 0;
    for(i = myoffset; i < myoffset + chunk; i++) {
        mysum += data[i];
    }
    printf("Task %d mysum = %lf\n", myid, mysum);
    return mysum;
}

int main (int argc, char *argv[])
{
    int numtasks, taskid, rc, dest, offset, i, j, tag1, 
        tag2, tagsum, source, chunksize, leftover;
    double mysum, sum, partial_sum;
    MPI_Status status;

    /***** Initializations *****/
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    printf ("MPI task %d has started...  ", taskid);
    chunksize = (ARRAYSIZE / numtasks);
    leftover = (ARRAYSIZE % numtasks);
    tag1 = 1;
    tag2 = 2;
    tagsum = 3;

    /***** Master task only ******/
    if (taskid == MASTER) {
        /* Initialize the array */
        sum = 0;
        for(i = 0; i < ARRAYSIZE; i++) {
            data[i] =  i * 1.0;
            sum = sum + data[i];
        }
        printf("Initialized array sum = %lf\n",sum);
        printf("numtasks= %d  chunksize= %d  leftover= %d\n", numtasks, chunksize, leftover);

        /* Send each task its portion of the array - master keeps 1st part plus leftover elements */
        offset = chunksize + leftover;
        for (dest = 1; dest < numtasks; dest++) {
            MPI_Send(&offset, 1, MPI_INT, dest, tag1, MPI_COMM_WORLD);
            MPI_Send(&data[offset], chunksize, MPI_DOUBLE, dest, tag2, MPI_COMM_WORLD);
            printf("Sent %d elements to task %d offset= %d\n", chunksize, dest, offset);
            offset = offset + chunksize;
        }

        /* Master does its part of the work */
        offset = 0;
        mysum = update(offset, chunksize + leftover, taskid);
        sum = mysum;

        /* Wait to receive results from each task */
        for (i = 1; i < numtasks; i++) {
            source = i;
            MPI_Recv(&partial_sum, 1, MPI_DOUBLE, source, tagsum, MPI_COMM_WORLD, &status);
            sum += partial_sum;
        }
        printf("*** Final sum= %lf ***\n",sum);
    }  /* end of master section */

    /***** Non-master tasks only *****/
    if (taskid > MASTER) {
        /* Receive my portion of array from the master task */
        source = MASTER;
        MPI_Recv(&offset, 1, MPI_INT, source, tag1, MPI_COMM_WORLD, &status);
        MPI_Recv(&data[offset], chunksize, MPI_DOUBLE, source, tag2, MPI_COMM_WORLD, &status);

        /* Do my part of the work */
        mysum = update(offset, chunksize, taskid);

        /* Send my results back to the master task */
        dest = MASTER;
        MPI_Send(&mysum, 1, MPI_DOUBLE, dest, tagsum, MPI_COMM_WORLD);
    } /* end of non-master */

    MPI_Finalize();

    return 0;
}
