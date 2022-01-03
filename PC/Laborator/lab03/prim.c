/**
 * Exercitiul 2.
 * Afisarea divizorilor nebanali pentru un numar sau mesajul PRIM.
 */
#include <stdio.h>
#include <stdbool.h>

int main()
{
    int x, i, primes = 0;
    bool prim;

    while(scanf("%d", &x) && x > 0) {
        prim = true;
        printf("OUT: ");
        for (i = 2; i < x; i++) {
            if (x % i == 0) {
                printf("%d ", i);
                prim = false;
            }
        }

        if (prim && x > 1) {
            printf("PRIM\n");
            primes++;
        } else {
            printf("\n");
        }
    }

    printf("OUT: S-au găsit %d numere prime.\n", primes);

    return 0;
}
