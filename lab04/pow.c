/**
 * Exercitiul 2. 
 * Subprogram recursiv pentru ridicarea la putere.
 */
#include <stdio.h>

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
