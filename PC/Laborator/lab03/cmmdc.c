/**
 * Bonus.
 * Cmmdc pentru n numere
 */
#include <stdio.h>

int main()
{
    int n, i, a, b, c;
    scanf("%d", &n);
    scanf("%d %d", &a, &b);

    while(b) {
        c = a % b;
        a = b;
        b = c;
    }

    for (i = 2; i < n; i++) {
        scanf("%d", &b);
        while(b) {
            c = a % b;
            a = b;
            b = c;
        }
    }

    printf("cmmdc: %d\n", a);

    return 0;
}
