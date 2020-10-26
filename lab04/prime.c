/**
 * Exercitiul 6. 
 * Determinarea celui mai apropiat numar prim fata de un numar citit
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool prim(int x) {
    if (x < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(x); i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int x;
    while(scanf("%d", &x) && x >= 0) {
        printf("* ");
        if (!prim(x)) {
            int st, dr;
            for (int i = x + 1; ; i++) {
                if (prim(i)) {
                    dr = i;
                    break;
                }
            }
            for (int i = x - 1; i >= 2; i--) {
                if (prim(i)) {
                    st = i;
                    break;
                }
            }

            if (abs(st - x) == abs(dr - x)) {
                printf("%d %d\n", st, dr);
            } else if (abs(st - x) < abs(dr - x)) {
                printf("%d\n", st);
            } else {
                printf("%d\n", dr);
            }
        } else {
            printf("\n");
        }
    }

    return 0;
}
