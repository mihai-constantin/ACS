/**
 * Demo pointeri
 */
#include <stdio.h>
#include <stdlib.h>

int incmod(int *n, int m) {
    return ++(*n) % m;
}

void f(int *a, int *b, int *c, int d) {
    *a = 20;
    *b = 50;
    *c = 70;
    d++;
}

int main()
{
    int *a;             /* pointer */
    int b = 5;          /* variabila */
    char *c;            /* pointer catre un caracter (sau sir de caractere) */
    void *buff = NULL;  /* pointer catre void, initializat cu NULL */

    // *a = 1; /* seg fault (asignare nevalida; a pointer neinitializat) */

    a = &b; /* a pointeaza catre adresa variabilei b */

    *a = 10; // b = 10
    printf("%d\n", b);

    /* pointeri in functii */
    int n = 10, m = 15;
    incmod(&n, m);
    printf("n: %d\n", n);

    int x = 0;
    int y = 0;
    int z = 0;
    int t = 0;
    f(&x, &y, &z, t);
    // in acest moment, x, y, z vor avea valorile finale din subprogramul f
    // t va ramane 0
    printf("%d %d %d %d\n", x, y, z, t);

    return 0;
}