/**
 * Exercitiul 3.
 * Afisarea unor numere dupa un interval de timp.
 */
#include <stdio.h>
#include <time.h>

void wait(int seconds) {
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC;
    while(clock() < endwait) {}
}

int main()
{
    for (int i = 3; i >= 1; i--) {
        printf("%d\n", i);
        wait(1);
    }
    printf("START\n");

    return 0;
}