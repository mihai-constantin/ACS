#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>

#define MASTER 0

int pwork = 1;
int cwork[4];

struct timeval startwtime, endwtime;
double arr_time;

int main(int argc, char** argv) 
{
    if (argc != 2) {
        printf("Usage: %s <dim>\n", argv[0]);
        exit(-1);
    }
    int dim = atoi(argv[1]);
    int* data = (int*) malloc(dim * sizeof(int));
    double* roots = (double*) malloc(dim * sizeof(double));

    /* start MPI Process */
    MPI_Init(&argc, &argv);

    int rank, nthreads;
    /* get the id (rank)*/
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    /* Get the total number of threads */
    MPI_Comm_size(MPI_COMM_WORLD, &nthreads);

    /* init data for all threads */
    for (int i = 0; i < dim; i++) {
        data[i] = i;
    }

    if (rank == MASTER) {
        gettimeofday(&startwtime, NULL);
    }

    /* Producer */
    if (rank == MASTER) {
        for (int idx = 1; idx < dim; idx++) {
            /* wait for a worker to become available */
            MPI_Status status;
            double root = 0;
            MPI_Recv(&root, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            /* if a root was computed */
            if (status.MPI_TAG > 0) {
                roots[status.MPI_TAG] = root;
            }

            pwork++;
            MPI_Send(&(data[idx]), 1, MPI_INT, status.MPI_SOURCE, idx, MPI_COMM_WORLD);
        }

        /* send termination signal to each rank when they submit their last job */
        for (int idx = 0; idx < nthreads-1; idx++) {
            /* wait for a worker to become available */
            MPI_Status status;
            double root = 0;
            MPI_Recv(&root, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            /* if a root was computed */
            if (status.MPI_TAG > 0) {
                roots[status.MPI_TAG] = root;
            }

            /* send termination signal (tag = 0) */
            MPI_Send(&idx, 1, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD);
        }
    } else { /* Consumer */
        /* announce myself to producer */
        double root = 0;
        MPI_Send(&root, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        bool terminated = false;

        do {
            /* wait for a job */
            int num = 0;
            MPI_Status status;
            MPI_Recv(&num, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (!status.MPI_TAG) {
                terminated = true;
            } else {
                cwork[rank] += 1;
                root = sqrt(num);
                MPI_Send(&root, 1, MPI_DOUBLE, 0, status.MPI_TAG, MPI_COMM_WORLD);
            }
        } while (!terminated);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == MASTER) {
        gettimeofday(&endwtime, NULL);
        arr_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
        printf("Time taken = %f\n", arr_time);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == MASTER) {
        for (int i = 0; i < dim; i++) {
            printf("sqrt(%i) = %f\n", data[i], roots[i]);
        }
        printf("work done by producer:  %d\n", pwork);
        printf("work done by consumers:\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    for (int i = 1; i < nthreads; i++) {
        if (rank == i) {
            printf("%d\n", cwork[i]);
        }
    }

    MPI_Finalize();
}