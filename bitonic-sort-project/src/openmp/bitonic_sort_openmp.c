// Bitonic Sort - arruential implementation
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <omp.h>

int *arr; // data array to be sorted
int n; // data array size
int p; // number of threads

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

void bitonic_sort_seq(int start, int length, int direction)
{
    int i;
    int split_length;

    if (length == 1)
        return;

    if (length % 2 !=0 )
    {
        printf("error\n");
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
    for (i = start; i < start + split_length; i++)
        compare(i, i + split_length, direction);

    bitonic_sort_seq(start, split_length, direction);
    bitonic_sort_seq(start + split_length, split_length, direction);
}

void bitonic_sort_par(int start, int length, int direction) {
    int i;
    int split_length;
    int m = n / p;

    if (length == 1)
        return;

    if (length % 2 !=0 ) {
        exit(0);
    }

    split_length = length / 2;

    // bitonic split
    #pragma omp parallel for shared(arr, direction, start, split_length) private(i)
    for (i = start; i < start + split_length; i++)
        compare(i, i + split_length, direction);

    if (split_length > m) {
        bitonic_sort_par(start, split_length, direction);
        bitonic_sort_par(start + split_length, split_length, direction);
    }
}

void sort(int direction) {
  int i, j, m = n / p;
  // make bitonic sequence - part 1
  for (i = 2; i <= m; i = 2 * i) {
      #pragma omp parallel for shared(i, arr) private(j, direction)
      for (j = 0; j < n; j += i)
          bitonic_sort_seq(j, i, (j / i) % 2 == 0 ? ASCENDING : DESCENDING);
  }

  // make bitonic sequence - part 2
  for (i = 2; i <= p; i = 2 * i) {
      for (j = 0; j < p; j += i)
          bitonic_sort_par(j*m, i*m,  (j / i) % 2 == 0 ? ASCENDING : DESCENDING);

      #pragma omp parallel for shared(j)
      for (j = 0; j < p; j++)
          bitonic_sort_seq(j*m, m,  (j / i) % 2 == 0 ? ASCENDING : DESCENDING);
  }
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

    // OpenMP - get number of threads
    p = 4;
    omp_set_num_threads(4);

    struct timeval startwtime, endwtime;
    double arr_time;

    init();
    gettimeofday(&startwtime, NULL);
    sort(ASCENDING); // sort the array in ascending order
    gettimeofday(&endwtime, NULL);
    arr_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time taken = %f\n", arr_time);
    test();
    free(arr);

    return 0;
}
