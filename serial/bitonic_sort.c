// Bitonic Sort - Sequential version
// Ascending sorting
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 1048576

void read_array(FILE *in, int arr[N], int n) {
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &arr[i]);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void compareAndSwap(int arr[N], int i, int j, int direction) {
    if ((arr[i] > arr[j]) == direction) {
        swap(&arr[i], &arr[j]);
    }
}

void bitonic_merge(int arr[N], int low, int cnt, int direction) {
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

void bitonic_sort(int arr[N], int low, int cnt, int direction) {
    if (cnt == 1) {
        return;
    }
    int k = cnt/2;
    bitonic_sort(arr, low, k, 1); // ascending order
    bitonic_sort(arr, low + k, k, 0); // descending order
    bitonic_merge(arr, low, cnt, direction); // merge
}

void sort(int arr[N], int n, int up) {
    bitonic_sort(arr, 0, n, up);
}

void print_array(FILE *out, int arr[N], int n) {
    for (int i = 0; i < n; i++) {
        fprintf(out, "%d ", arr[i]);
    }
    fprintf(out, "\n");
}

int main()
{
    int arr[N], n;
    struct timeval startwtime, endwtime;
    double seq_time;

    FILE *in, *out;
    in = fopen("data.in", "r");
    out = fopen("data.out", "w");
    
    fscanf(in, "%d", &n); // array's dimension
    read_array(in, arr, n);
    gettimeofday(&startwtime, NULL);
    sort(arr, n, 1); // sort the array in ascending order
    gettimeofday(&endwtime, NULL);

    seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time taken = %f\n", seq_time);

    print_array(out, arr, n);

    return 0;
}