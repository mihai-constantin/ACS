/**
 * Exercitiul 3. 
 * Afisarea unui numar in diverse baze de numeratie. 
 */
#include <stdio.h>

int main()
{
    int x;

    scanf("%d", &x);
    
    printf("Baza 10: %d\n", x);
    printf("Baza 8: %o\n", x);
    printf("Baza 16: %x\n", x);
    printf("Baza 16: %X\n", x);

    return 0;
}
