/**
 * Demo pointeri
 */
#include <stdio.h>
#include <stdlib.h>

int incmod(int *n, int m) {
    return ++(*n) % m;
}

int main()
{
    int *a;             /* pointer */
    int b = 5;          /* variabila */
    char *c;            /* pointer catre un caracter (sau sir de caractere) */
    void *buff = NULL;  /* pointer catre void, initializat cu NULL */

    // *a = 1; /* seg fault (asignare nevalida; a pointer neinitializat) */

    a = &b; /* a pointeaza catre adresa variabilei b */

    *a = 10;
    printf("%d\n", b);

    /* pointeri in functii */
    int n = 10, m = 15;
    incmod(&n, m);
    printf("n: %d\n", n);

    return 0;
}