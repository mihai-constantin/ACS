// Bitonic Sort - Sequential version
// Ascending sorting
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

#define N 1048576

ifstream in("data.in");
ofstream out("data.out");

void read_array(int arr[N], int n) {
    for (int i = 0; i < n; i++) {
        in >> arr[i];
    }
}

void compareAndSwap(int arr[N], int i, int j, int direction) {
    if ((arr[i] > arr[j]) == direction) {
        swap(arr[i], arr[j]);
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

void print_array(int arr[N], int n) {
    for (int i = 0; i < n; i++) {
        out << arr[i] << " ";
    }
    out << '\n';
}

int main()
{
    int arr[N], n;
    
    in >> n; // array's dimension
    read_array(arr, n);
    sort(arr, n, 1); // sort the array in ascending order
    print_array(arr, n);

    return 0;
}