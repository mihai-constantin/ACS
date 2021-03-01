#include<mpi.h>
#include<stdio.h>

/**
 * @author cristian.chilipirea
 * Run: mpirun -np 2 ./a.out
 */

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	int v;
	MPI_Init(&argc, &argv);
	MPI_Status stat;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	if(rank==0) {
		MPI_Send(&v, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		printf("Got here! MPI_Send is non-blocking because there is no one to do a receive.\n");
	} else {
		sleep(10);
	}

	printf("Bye from %i/%i\n", rank, nProcesses);
	MPI_Finalize();
	return 0;
}