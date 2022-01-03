/**
 * Exercitiul 2. 
 * Selection sort
 */
#include <stdio.h>

#define N 100

void read_array(int v[N], int n) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void selection_sort(int v[N], int n) {
    int i, j, pos_min, aux;
    for (i = 0; i < n - 1; i++) {
        pos_min = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[pos_min]) {
                pos_min = j;
            }
        }
        // interschimbare v[i] cu v[pos_min]
        aux = v[i];
        v[i] = v[pos_min];
        v[pos_min] = aux;
    }
}

void print_array(int v[N], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int v[N], n;

    scanf("%d", &n);
    read_array(v, n);

    selection_sort(v, n);
    print_array(v, n);

    return 0;
}
