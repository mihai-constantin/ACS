#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 10

/**
 * @author cristian.chilipirea
 *
 */

int ans[N];
int vQSort[N];
int v[N];

void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	int displayWidth = 2 + log10(v[N-1]);
	for(i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}

int main (int argc, char *argv[])
{
    int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	// printf("Hello from %i/%i\n", rank, nProcesses);	

    int number = -1;
    int number1;
    
	if(rank == nProcesses - 1){
		int sorted = 0;
		int aux;

		// generate the vector v with random values
		srand(42);
		for(int i = 0; i < N; i++)
			v[i] = rand()%N;

		printf("Vector initial: ");
		for(int i = 0; i < nProcesses; i++) {
    		printf("%d ", v[i]);
    	}
    	printf("\n");

		// make copy to check it against qsort
		for(int i = 0; i < N; i++)
			vQSort[i] = v[i];
		qsort(vQSort, N, sizeof(int), cmp);

		for(int i = 0; i < nProcesses; i++){
			MPI_Send(&v[i], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}
	
	for(int i = 0; i < nProcesses-rank; i++) {
		if(rank == 0) {
			MPI_Recv(&number1, 1, MPI_INT, nProcesses - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		} else {
			MPI_Recv(&number1, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}

		if(number == -1){
			number = number1;
		}else{
			if(number > number1){
				int a = number;
				number = number1;
				MPI_Send(&a, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
			}else{
				MPI_Send(&number1, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
			}
		}
		
	}

    MPI_Gather(&number, 1, MPI_INT, &ans[rank], 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
		printf("Vector sortat : ");
    	for(int i = 0; i < nProcesses; i++) {
    		printf("%d ", ans[i]);
    	}
    	printf("\n");
    }

    MPI_Finalize();

    return 0;

}