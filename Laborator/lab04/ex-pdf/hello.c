#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
    int nProcesses;
    int rank;

    // initialize the MPI execution environment
    MPI_Init(&argc, &argv);

    // determine the number of processes in a Communicator
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    // get the task id from a Communicator
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    printf("Hello from %d/%d\n", rank, nProcesses);

    MPI_Finalize();

    return 0;
}
