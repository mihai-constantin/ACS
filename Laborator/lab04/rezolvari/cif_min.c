/**
 * Subprogram recursiv pentru determinarea cifrei minime a unui numar dat.
 */
#include <stdio.h>
#include <stdbool.h>

int min(int x, int y) {
    if (x < y) {
        return x;
    }
    return y;
}

int cif_min(int x) {
    if (x < 10) {
        return x;
    }
    return min(x % 10, cif_min(x/10));
}

int main()
{
    int x;
    scanf("%d", &x);

    printf("%d\n", cif_min(x));

    return 0;
}
