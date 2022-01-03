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
	int leader = rank;
	int newLeader;
	float myVal;
	float newVal;

	for(int k=0;k<100;k++){
		for(int i=0;i<30;i++){
			if(graph[i][0] == rank){
				MPI_Send(&leader, 1, MPI_INT, graph[i][1], 0, 
					MPI_COMM_WORLD);
			}
		}

		for(int i=0;i<30;i++){
			if(graph[i][1] == rank){
				MPI_Recv(&newLeader, 1, MPI_INT, MPI_ANY_SOURCE, 0, 
					MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				if(newLeader>leader){
					leader=newLeader;
				}
			}
		}
	}

	printf("leader = %d\n", leader);	

	MPI_Barrier(MPI_COMM_WORLD);

	if(rank == leader) {
		myVal = 1;
	} else myVal = 0;

	for(int c=0; c<1000; c++) {
		for(int i=0; i<30; i++) {
			if(graph[i][0] == rank) {
				MPI_Sendrecv(&myVal, 1, MPI_FLOAT, graph[i][1], 0,
                	&newVal, 1, MPI_FLOAT, MPI_ANY_SOURCE, 0,
                	MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				myVal = (myVal + newVal)/2;
			}
		}
	}

	printf("val = %f\n", myVal);

	MPI_Finalize();
	return 0;
}