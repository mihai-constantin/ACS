/**
 * Algoritmul CREW-PRAM cu n^3 procesoare pentru inmultire de matrici
 * C <- A * B
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

/**
 * Se considera un numar de procesoare egal cu n^3, unde n este dimensiunea matricei.
 * 
 * Algoritmul consta in 2 etape
 * 1. Fiecare procesor P(i,j,k) calculeaza in paralel produsul A[i][j] * B[j][k].
 * 2. Reducere prin insumare.
 */

typedef struct Index {
    int i;
    int j;
    int k;
} Index;

#define n 4

int A[n][n];
int B[n][n];
int C[n][n][n];

pthread_barrier_t barrier;

void read() {
    int i;
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }
}

void* threadFunction(void* var) {

    Index thread_id = *(Index*) var;

    // 1. partial result
    C[thread_id.i][thread_id.j][thread_id.k] = A[thread_id.i][thread_id.k] * B[thread_id.k][thread_id.j];
    printf("Thread [%d %d %d]: %d\n", thread_id.i, thread_id.j, thread_id.k, C[thread_id.i][thread_id.j][thread_id.k]);

    pthread_barrier_wait(&barrier);

    // 2. add to final result
    for (int i = 0; i < (int)(log2(n)); i++) {
        if (thread_id.k % (int)(pow(2, i + 1)) == 0) {
            C[thread_id.i][thread_id.j][thread_id.k] += C[thread_id.i][thread_id.j][thread_id.k + (int)(pow(2, i))];
        }
        pthread_barrier_wait(&barrier);
    }

    return NULL;
}

void print() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", C[i][j][0]);
        }
        printf("\n");
    }
}

int main()
{
    int N = n * n * n; // n^3 procesoare

    read();

    // create thread_id vector
    // each thread is characterised by three indices (i, j, k) specific to the processor
    struct Index thread_id[N];
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                thread_id[idx].i = i;
                thread_id[idx].j = j;
                thread_id[idx].k = k;
                idx++;
            }
        }
    }

    // init barier
    pthread_barrier_init(&barrier, NULL, N);

    // create N threads
	pthread_t tid[N];
	for(int i = 0; i < N; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

    for(int i = 0; i < N; i++) {
		pthread_join(tid[i], NULL);
	}

    // distroy barrier
    pthread_barrier_destroy(&barrier);

    print();

    return 0;
}
