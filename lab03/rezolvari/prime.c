/**
 * Determinarea celor mai mari 2 numere prime citite
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main()
{   
    int x, max1 = -1, max2 = -1;
    bool prim;

    while(scanf("%d", &x) && x >= 0) {
        prim = true; // pp ca numarul x e prim
        if (x < 2) {
            prim = false;
        } else {
            for (int i = 2; i <= sqrt(x); i++) {
                if (x % i == 0) {
                    prim = false;
                    break;
                }
            }
        }

        if (prim) {
            if (max1 == -1) {
                // initializez max1 cu prima valoare prima gasita
                max1 = x;
            } else if (x > max1) {
                max2 = max1;
                max1 = x;
            } else if (x > max2) {
                max2 = x;
            }
        }

    }

    printf("%d %d\n", max1, max2);
    
    return 0;
}
