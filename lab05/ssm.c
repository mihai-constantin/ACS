/**
 * Exercitiul 4. 
 * Subsecventa de suma maxima
 */
#include <stdio.h>

#define N 100

void read_array(int arr[N], int dim) {
    int i;
    for (i = 0; i < dim; i++) {
        scanf("%d", &arr[i]);
    }
}

int max(int x, int y) {
    if (x > y) {
        return x;
    }
    return y;
}

void ssm(int v[N], int n) {
    int i, maxim, bst[N];
    bst[0] = v[0];
    maxim = bst[0];
    for (i = 1; i < n; i++) {
        bst[i] = max(bst[i - 1] + v[i], v[i]);
        if (maxim < bst[i]) {
            maxim = bst[i];
        }
    }
    printf("maxim: %d\n", maxim);
}

int main()
{
    int v[N], n;

    scanf("%d", &n);
    read_array(v, n);  

    ssm(v, n);

    return 0;
}
