// Bitonic Sort - Sequential implementation
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

int *arr; // data array to be sorted
int n; // data array size

const int ASCENDING = 1;
const int DESCENDING = 0;

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

void bitonic_sort(int low, int cnt, int direction) {
    if (cnt == 1) {
        return;
    }
    int k = cnt/2;
    bitonic_sort(low, k, 1); // ascending order
    bitonic_sort(low + k, k, 0); // descending order
    bitonic_merge(low, cnt, direction); // merge
}

void sort(int order_type) {
    bitonic_sort(0, n, order_type);
}

void test() {
    bool pass = true;
    for (int i = 1; i < n; i++) {
        pass &= (arr[i - 1] <= arr[i]);
    }
    printf("TEST %s\n", (pass) ? "PASSED!" : "FAILED!");
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        printf("Usage: %s 2^<array length>\n", argv[0]);
        exit(1);
    }

    n = (1 << atoi(argv[1]));
    arr = (int*) malloc(n * sizeof(int));

    struct timeval startwtime, endwtime;
    double seq_time;

    init();
    gettimeofday(&startwtime, NULL);
    sort(ASCENDING); // sort the array in ascending order
    gettimeofday(&endwtime, NULL);
    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time taken = %f\n", seq_time);
    test();
    free(arr);

    return 0;
}