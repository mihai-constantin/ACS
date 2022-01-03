/**
 * Verificare daca un numar este par.
 */
#include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    
    // Metoda 1: si pe biti
    if ((x & 1) == 0) {
        printf("par\n");
    } else {
        printf("impar\n");
    }

    // Metoda 2: modulo
    if (x % 2 == 0) {
        printf("par\n");
    } else {
        printf("impar\n");
    }

    return 0;
}