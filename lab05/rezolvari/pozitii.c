/**
 *  Exercitiul 2
 *  Sa se afiseze elementele de pe pozitiile pare ale unui vector, dupa care, pe o linie noua, cele de pe pozitii impare.
 */
#include <stdio.h>

#define N 1000000

void read_array(int v[N], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void print_even_pos(int v[N], int n) {
    int i;
    for (i = 0; i < n; i += 2) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void print_odd_pos(int v[N], int n) {
    int i;
    for (i = 1; i < n; i += 2) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int v[N], n;
    scanf("%d", &n);
    read_array(v, n);
    print_even_pos(v, n);
    print_odd_pos(v, n);

    return 0;
}
