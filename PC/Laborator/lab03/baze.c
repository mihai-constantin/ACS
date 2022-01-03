/**
 * Exercitiul 4.
 * Conversie numere din baza 10 in baza 2 si invers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int x, nr10, idx, base, i;

    int* res = (int*) malloc(20 * sizeof(int));

    while(scanf("%d", &x) && x > 0) {
        scanf("%d", &base);
        idx = 0;
        if (base == 2) {
            nr10 = 0;
            while(x > 0) {
                nr10 += (int)pow(2, idx) * (x % 10);
                idx++;
                x /= 10;
            }
            printf("%d\n", nr10);
        } else {
            while(x) {
                res[idx++] = x % 2;
                x /= 2;
            }
            for (i = idx - 1; i >= 0; i--) {
                printf("%d", res[i]);
            }
            printf("\n");
        }
    }

    free(res);

    return 0;
}
