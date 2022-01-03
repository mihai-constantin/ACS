/**
 * Exercitiul 1. 
 * Subprogram pentru suma a doua numere.
 */
#include <stdio.h>

int sum(int a, int b) {
    int s = a + b;
    return s;
}

int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("Suma este %d\n", sum(a, b));
    return 0;
}
