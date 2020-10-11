/**
 * Exercitiul 5.
 * Generare de numere aleatoare.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int x;
    srand((unsigned)time(NULL)); 
    for (int i = 0; i < 5; i++) {
        x = rand();
        printf("%d\n", x);
    }

    return 0;
}