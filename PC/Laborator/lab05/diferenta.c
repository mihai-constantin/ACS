/**
 * Exercitiul 3. 
 * Diferenta a doi vectori
 */
#include <stdio.h>
#include <stdbool.h>

#define N 100

void read_array(int arr[N], int dim) {
    int i;
    for (i = 0; i < dim; i++) {
        scanf("%d", &arr[i]);
    }
}

bool find_elem(int arr[N], int dim, int elem) {
    int i;
    for (i = 0; i < dim; i++) {
        if (arr[i] == elem) {
            return true;
        }
    }
    return false;
}

void dif(int a[N], int n, int b[N], int m) {
    int i;
    for (i = 0; i < n; i++) {
        if (!find_elem(b, m, a[i])) {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
}

int main()
{
    int a[N], b[N];
    int n, m;

    scanf("%d", &n);
    read_array(a, n);   

    scanf("%d", &m);
    read_array(b, m);

    dif(a, n, b, m);

    return 0;
}
