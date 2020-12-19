// Bitonic Sort - Pthreads implementation
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

int *arr; // data array to be sorted
int n; // data array size
int thread_layers;
int thread_count = 0;

const int ASCENDING = 1;
const int DESCENDING = 0;

typedef struct thread_data {
    int low;
    int cnt;
    int direction;
    int layer;
} thread_data;

int asc(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}

int desc(const void *a, const void *b) {
    return ( *(int*)b - *(int*)a );
}

void init() {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void compare(int i, int j, int direction) {
    if ((arr[i] > arr[j]) == direction) {
        swap(&arr[i], &arr[j]);
    }
}

void bitonic_merge(int low, int cnt, int direction) {
    if (cnt == 1) {
        return;
    }
    int k = cnt/2;
    for (int i = low; i < low + k; i++) {
        compare(i, i + k, direction);
    }
    bitonic_merge(low, k, direction);
    bitonic_merge(low + k, k, direction);
}

void* pthread_bitonic_merge(void* arg) {
    int low = ((thread_data *) arg) -> low;
    int cnt = ((thread_data *) arg) -> cnt;
    int direction = ((thread_data *) arg) -> direction;
    int layer = ((thread_data *) arg) -> layer;
    if (cnt == 1) {
        return NULL;
    }

    int k = cnt/2;
    for (int i = low; i < low + k; i++) {
        compare(i, i + k, direction);
    }

    if (layer <= 0) {
        bitonic_merge(low, k, direction);
        bitonic_merge(low + k, k, direction);
        return NULL;
    }

    thread_data thread_data1, thread_data2;
    pthread_t thread1, thread2;
    thread_data1.low = low;
    thread_data1.cnt = k;
    thread_data1.direction = direction;
    thread_data1.layer = layer - 1;
    pthread_create(&thread1, NULL, pthread_bitonic_merge, &thread_data1);

    thread_data2.low = low + k;
    thread_data2.cnt = k;
    thread_data2.direction = direction;
    thread_data2.layer = layer - 1;
    pthread_create(&thread2, NULL, pthread_bitonic_merge, &thread_data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return NULL;
}

void* pthread_bitonic_sort(void* arg) {
    int low = ((thread_data *) arg) -> low;
    int cnt = ((thread_data *) arg) -> cnt;
    int direction = ((thread_data *) arg) -> direction;
    int layer = ((thread_data *) arg) -> layer;
    if (cnt == 1) {
        return NULL;
    }

    int k = cnt/2;
    if (layer >= thread_layers) {
        qsort(arr + low, k, sizeof(int), asc);
        qsort(arr + low + k, k, sizeof(int), desc);
    } else {
        thread_data thread_data1, thread_data2;
        pthread_t thread1, thread2;

        thread_data1.low = low;
        thread_data1.cnt = k;
        thread_data1.direction = ASCENDING;
        thread_data1.layer = layer + 1;
        thread_count++;
        pthread_create(&thread1, NULL, pthread_bitonic_sort, &thread_data1);

        thread_data2.low = low + k;
        thread_data2.cnt = k;
        thread_data2.direction = DESCENDING;
        thread_data2.layer = layer + 1;
        thread_count++;
        pthread_create(&thread2, NULL, pthread_bitonic_sort, &thread_data2);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
    }

    thread_data thread_data3;
    thread_data3.low = low;
    thread_data3.cnt = cnt;
    thread_data3.direction = direction;
    thread_data3.layer = thread_layers - layer;
    pthread_bitonic_merge(&thread_data3);

    return NULL;
}

void pthread_sort() {
    thread_data thread_data;
    thread_data.low = 0;
    thread_data.cnt = n;
    thread_data.direction = ASCENDING;
    thread_data.layer = 0;
    pthread_bitonic_sort(&thread_data);
}

void test() {
    bool pass = true;
    for (int i = 1; i < n; i++) {
        pass &= (arr[i - 1] <= arr[i]);
    }
    printf("TEST %s\n", (pass) ? "PASSED!" : "FAILED!");
}

void print() {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Usage: %s 2^<array length> 2^<number of threads>\n", argv[0]);
        exit(1);
    }

    n = (1 << atoi(argv[1]));
    arr = (int*) malloc(n * sizeof(int));

    thread_layers = atoi(argv[2]);
    if (thread_layers != 0 && thread_layers != 1) {
        thread_layers--;
    }

    struct timeval startwtime, endwtime;
    double seq_time;

    init();
    gettimeofday(&startwtime, NULL);
    pthread_sort(); // sort the array in ascending order
    gettimeofday(&endwtime, NULL);
    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time taken = %f\n", seq_time);
    printf("Total threads used: %d\n", thread_count);
    test();
    free(arr);
    
    return 0;
}
