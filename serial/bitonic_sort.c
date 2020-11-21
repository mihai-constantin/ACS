// Bitonic Sort - Sequential version
// Ascending sorting
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

void init(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void compareAndSwap(int *arr, int i, int j, int direction) {
    if ((arr[i] > arr[j]) == direction) {
        swap(&arr[i], &arr[j]);
    }
}

void bitonic_merge(int *arr, int low, int cnt, int direction) {
    if (cnt == 1) {
        return;
    }
    int k = cnt/2;
    for (int i = low; i < low + k; i++) {
        compareAndSwap(arr, i, i + k, direction);
    }
    bitonic_merge(arr, low, k, direction);
    bitonic_merge(arr, low + k, k, direction);
}

void bitonic_sort(int *arr, int low, int cnt, int direction) {
    if (cnt == 1) {
        return;
    }
    int k = cnt/2;
    bitonic_sort(arr, low, k, 1); // ascending order
    bitonic_sort(arr, low + k, k, 0); // descending order
    bitonic_merge(arr, low, cnt, direction); // merge
}

void sort(int *arr, int n, int up) {
    bitonic_sort(arr, 0, n, up);
}

void test(int *arr, int n) {
    bool pass = true;
    for (int i = 1; i < n; i++) {
        pass &= (arr[i - 1] <= arr[i]);
    }
    printf("TEST %s\n", (pass) ? "PASSED!" : "FAILED!");
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <array length>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    int* arr = (int*) malloc(n * sizeof(int));

    struct timeval startwtime, endwtime;
    double seq_time;

    init(arr, n);
    gettimeofday(&startwtime, NULL);
    sort(arr, n, 1); // sort the array in ascending order
    gettimeofday(&endwtime, NULL);
    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time taken = %f\n", seq_time);
    test(arr, n);
    free(arr);

    return 0;
}