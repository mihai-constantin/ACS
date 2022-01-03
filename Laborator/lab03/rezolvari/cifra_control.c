/**
 * Cifra de control a unui numar
 */
#include <stdio.h>

int main()
{
    int x, s;
    scanf("%d", &x);
    while(x > 9) {
        s = 0;
        while(x) {
            s += x % 10;
            x /= 10;
        }
        x = s;
    }
    printf("%d\n", x);
    return 0;
}
