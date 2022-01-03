#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"
#include <stdbool.h>

#define MASTER 0

// Globals
double timer_start;
double timer_end;
int process_rank;
int num_processes;
int *arr;
int n;

void init() {
  for (int i = 0; i < n; i++)
    arr[i] = rand() % n;
}

int ComparisonFunc(const void * a, const void * b) {
    return ( * (int *)a - * (int *)b );
}

/* Sends the biggest of the list and receive the smallest of the list */
void CompareLow(int j) {
    int i, min;

    // Exchange with a neighbor whose (d-bit binary) processor number differs only at the jth bit.
    int send_counter = 0;
    int * buffer_send = malloc((n + 1) * sizeof(int));
    MPI_Send(
        &arr[n - 1],                // entire arr
        1,                          // one data item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // Receive new min of sorted numbers
    int * buffer_recieve = malloc((n + 1) * sizeof(int));
    MPI_Recv(
        &min,                       // buffer the message
        1,                          // one data item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message received
    );

    // Buffers all values which are greater than min send from H Process.
    for (i = 0; i < n; i++) {
        if (arr[i] > min) {
            buffer_send[send_counter + 1] = arr[i];
            send_counter++;
        } else {
            break;
        }
    }

    buffer_send[0] = send_counter;

    // send partition to paired H process
    MPI_Send(
        buffer_send,                // Send values that are greater than min
        send_counter,               // # of items sent
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // receive info from paired H process
    MPI_Recv(
        buffer_recieve,             // buffer the message
        n,                          // whole arr
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message received
    );

    // Take received buffer of values from H Process which are smaller than current max
    for (i = 1; i < buffer_recieve[0] + 1; i++) {
        if (arr[n - 1] < buffer_recieve[i]) {
            // Store value from message
            arr[n - 1] = buffer_recieve[i];
        } else {
            break;
        }
    }

    qsort(arr, n, sizeof(int), ComparisonFunc);

    // Reset the state of the heap from Malloc
    free(buffer_send);
    free(buffer_recieve);

    return;
}

void CompareHigh(int j) {
    int i, max;

    // Receive max from L Process's entire arr
    int recv_counter;
    int * buffer_recieve = malloc((n + 1) * sizeof(int));
    MPI_Recv(
        &max,                       // buffer max value
        1,                          // one item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message received
    );

    // Send min to L Process of current process's arr
    int send_counter = 0;
    int * buffer_send = malloc((n + 1) * sizeof(int));
    MPI_Send(
        &arr[0],                    // send min
        1,                          // one item
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // Buffer a list of values which are smaller than max value
    for (i = 0; i < n; i++) {
        if (arr[i] < max) {
            buffer_send[send_counter + 1] = arr[i];
            send_counter++;
        } else {
            break;
        }
    }

    // Receive blocks greater than min from paired slave
    MPI_Recv(
        buffer_recieve,             // buffer message
        n,                          // whole arr
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD,             // default comm.
        MPI_STATUS_IGNORE           // ignore info about message receiveds
    );
    recv_counter = buffer_recieve[0];

    // send partition to paired slave
    buffer_send[0] = send_counter;
    MPI_Send(
        buffer_send,                // all items smaller than max value
        send_counter,               // # of values smaller than max
        MPI_INT,                    // INT
        process_rank ^ (1 << j),    // paired process calc by XOR with 1 shifted left j positions
        0,                          // tag 0
        MPI_COMM_WORLD              // default comm.
    );

    // Take received buffer of values from L Process which are greater than current min
    for (i = 1; i < recv_counter + 1; i++) {
        if (buffer_recieve[i] > arr[0]) {
            // Store value from message
            arr[0] = buffer_recieve[i];
        } else {
            break;
        }
    }

    qsort(arr, n, sizeof(int), ComparisonFunc);

    // Reset the state of the heap from Malloc
    free(buffer_send);
    free(buffer_recieve);

    return;
}

void test() {
    bool pass = true;
    for (int i = 1; i < n; i++) {
        pass &= (arr[i - 1] <= arr[i]);
    }
    printf("TEST %s\n", (pass) ? "PASSED!" : "FAILED!");
}

int main(int argc, char * argv[]) {
    int i, j;

    // Initialization, get # of processes & this PID/rank
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    // Initialize arr for Storing Random Numbers
    n = (1 << atoi(argv[1]));
    arr = (int *) malloc(n * sizeof(int));

    init();

    // Blocks until all processes have finished generating
    MPI_Barrier(MPI_COMM_WORLD);

    // Cube Dimension
    int dimensions = (int)(log2(num_processes));

    // Start Timer before starting first sort operation (first iteration)
    if (process_rank == MASTER) {
        printf("Number of Processes spawned: %d\n", num_processes);
        timer_start = MPI_Wtime();
    }

    qsort(arr, n, sizeof(int), ComparisonFunc);

    // Bitonic Sort follows
    for (i = 0; i < dimensions; i++) {
        for (j = i; j >= 0; j--) {
            // (window_id is even AND jth bit of process is 0)
            // OR (window_id is odd AND jth bit of process is 1)
            if (((process_rank >> (i + 1)) % 2 == 0 && (process_rank >> j) % 2 == 0) || ((process_rank >> (i + 1)) % 2 != 0 && (process_rank >> j) % 2 != 0)) {
                CompareLow(j);
            } else {
                CompareHigh(j);
            }
        }
    }

    // Blocks until all processes have finished sorting
    MPI_Barrier(MPI_COMM_WORLD);

    if (process_rank == MASTER) {
        timer_end = MPI_Wtime();

        test();
        printf("Time Elapsed (Sec): %f\n", timer_end - timer_start);
    }

    free(arr);

    // Done
    MPI_Finalize();
    return 0;
}
