#include<mpi.h>
#include<stdio.h>

/**
 * @author cristian.chilipirea
 * Run: mpirun -np 10 ./a.out
 */

int graph[][2] = { { 0, 1 }, { 0, 4 }, { 0, 5 }, 
                  { 1, 0 }, { 1, 2 }, { 1, 6 }, 
                  { 2, 1 }, { 2, 3 }, { 2, 7 },
                  { 3, 2 }, { 3, 4 }, { 3, 8 },
                  { 4, 0 }, { 4, 3 }, { 4, 9 },
                  { 5, 0 }, { 5, 7 }, { 5, 8 },
                  { 6, 1 }, { 6, 8 }, { 6, 9 },
                  { 7, 2 }, { 7, 5 }, { 7, 9 },
                  { 8, 3 }, { 8, 5 }, { 8, 6 },
                  { 9, 4 }, { 9, 6 }, { 9, 7 } };


int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	
	int v[10];
	int received[10];
	int i,j;

	for(int i=0; i<10; i++) {
		v[i] = -1;
		received[i] = -1;
	}


	if (rank == 0) {
		for(int i=0; i<30; i++) {
			if (graph[i][0] == 0 && graph[i][1] != v[rank]) {
				MPI_Send(&v, 10, MPI_INT, graph[i][1], 0, 
					MPI_COMM_WORLD);
			}
		}

		for (i = 0; i < 30; i++) {
			if (graph[i][0] == rank && graph[i][1] != v[rank]) {
				printf("Process with rank %d receiving from %d\n", rank, graph[i][1]);
				MPI_Recv(&received, 10, MPI_INT, graph[i][1], 0, MPI_COMM_WORLD, &status);
				printf("Process with rank %d received from %d\n", rank, graph[i][1]);

				for (j = 0; j < 10; j++) {
					if (received[j] != -1) {
						v[j] = received[j];
					}
				}
			}
		}

		for (i = 0; i < 10; i++) {
			if (v[i] == rank) {
				MPI_Send(&v, 10, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
		}

	} else {
		MPI_Recv(&received, 10, MPI_INT, MPI_ANY_SOURCE, 0, 
					MPI_COMM_WORLD, &status);
		v[rank] = status.MPI_SOURCE;
		

		for (i = 0; i < 30; i++) {
			if (graph[i][0] == rank && graph[i][1] != v[rank]) {
				printf("Process with rank %d sent to %d\n", rank, graph[i][1]);
				MPI_Send(&v, 10, MPI_INT, graph[i][1], 0, MPI_COMM_WORLD);
			}
		}

		for (i = 0; i < 30; i++) {
			if (graph[i][0] == rank && graph[i][1] != v[rank]) {
				printf("Process with rank %d receiving from %d\n", rank, graph[i][1]);
				MPI_Recv(&received, 10, MPI_INT, graph[i][1], 0, MPI_COMM_WORLD, &status);
				printf("Process with rank %d received from %d\n", rank, graph[i][1]);

				for (j = 0; j < 10; j++) {
					if (received[j] != -1) {
						v[j] = received[j];
					}
				}
			}
		}

		MPI_Send(&v, 10, MPI_INT, v[rank], 0, MPI_COMM_WORLD);

		MPI_Recv(&v, 10, MPI_INT, v[rank], 0, MPI_COMM_WORLD, &status);

		for (i = 0; i < 10; i++) {
			if (v[i] == rank) {
				MPI_Send(&v, 10, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
		}
	}

	printf("\n-----------------------\n");
	for(int i=0; i<10; i++){
		printf("%d ", v[i]);
	}
	printf("\n-----------------------\n");

	MPI_Finalize();
	return 0;
}