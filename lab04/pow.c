/**
 * Exercitiul 2. 
 * Subprogram recursiv pentru ridicarea la putere.
 */
#include <stdio.h>

/**
 *  f(2, 5) = 2 * f(2, 4) = 2 * 2 * 2 * 2 * 2 * 1  = 2^5 = 32 
 *  f(2, 4) = 2 * f(2, 3) = 2 * 2 * 2 * 2 * 1 
 *  f(2, 3) = 2 * f(2, 2) = 2 * 2 * 2 * 1
 *  f(2, 2) = 2 * f(2, 1) = 2 * 2 * 1
 *  f(2, 1) = 2 * f(2, 0) = 2 * 1
 *  f(2, 0) = 1
 */
int putere(int a, int b) {
    if (!b) {
        return 1;
    }
    return a * putere(a, b - 1);
}

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d^%d = %d\n", a, b, putere(a, b));

    return 0;
}
