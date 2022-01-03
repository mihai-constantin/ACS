/**
 *  Exercitiul 1
 *  Se da un vector de n elemente. Sa se roteasca vectorul cu k pozitii la stanga.
 */
#include <stdio.h>

#define N 1000000

void read_array(int v[N], int n, int k) {
    for (int i = 0; i < n; i++) {
        // calculam pozitia pe care ar trebui sa fie elementul de la pozitia i in urma rotirii spre stanga cu k pozitii
        int pos = (n + (i - k)) % n;
        scanf("%d", &v[pos]); 
    }
}

void print_arry(int v[N], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int v[N], n, k;
    scanf("%d %d", &n, &k);
    k = k % n;
    read_array(v, n, k);
    print_arry(v, n);

    return 0;
}
