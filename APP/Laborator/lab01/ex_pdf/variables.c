#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {

    int a = 2, b = 3, c = 4;

    /*
        Aici variabilele a = 2, b = 3 si c = 4 au aceste valori pe thread-ul MASTER.
        De ce, avand in vedere ca in portiunea paralela intra si thread-ul 0 (MASTER),
        la final cand afisez variabilele a si b raman valorile 2 si 3 de la inceput?
        Inteleg ca valoarea c din 4 devine 3 pentru ca este partajata, dar daca a = 1
        si b = 2 pentru fiecare thread in parte, la final la printf cand afisez valorile
        a si b ale thread-ului MASTER, de ce nu se afiseaza 1 si 2?
    */

    printf("Master thread id: %d\n", omp_get_thread_num());

    #pragma omp parallel private(a, b) shared(c)
    {
        printf("Thread id: %d\n", omp_get_thread_num());
        a = 1;
        b = 2;
        c = a + b;
    }

    printf("[%d] %d %d %d\n", omp_get_thread_num(), a, b, c);

    return 0;
}
