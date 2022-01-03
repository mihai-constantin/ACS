/**
 * Exercitiul 5.
 * Verificare nr palindrom
 */
#include <stdio.h>

int main()
{
    int x, ogl = 0, aux;
   
    scanf("%d", &x);
    aux = x;
    while(aux) {
        ogl = ogl * 10 + aux % 10;
        aux /= 10;
    }
    if (x == ogl) {
        printf("Numarul %d este palindrom\n", x);
    } else {
        printf("Numarul %d nu este palindrom\n", x);
    }

    return 0;
}
