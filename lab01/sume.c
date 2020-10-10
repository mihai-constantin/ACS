/**
 * Exercitiul 5. 
 * Suma primelor n numere, respectiv a patratelor acestora. 
 */
#include <stdio.h>

int main()
{
    int n;

    scanf("%d", &n);
    
    int s1 = n * (n + 1) / 2;
    int s2 = n * (n + 1) * (2*n + 1) / 6;

    printf("%d %d\n", s1, s2);

    return 0;
}
