/**
 * Exercitiul 4. 
 * Suma, diferenta si media a doua numere reale afisate cu 5 zecimale. 
 */
#include <stdio.h>

int main()
{
    double a, b;

    scanf("%lf %lf", &a, &b);
    
    printf("Suma: %.5lf\n", a + b);
    printf("Diferenta: %.5lf\n", a - b);
    printf("Media: %.5lf\n", (a + b)/2);

    return 0;
}
