/**
 * Exercitiul 7. 
 * Determinarea daca 2 numere sunt egale cu o precizie de 4 zecimale.
 */
#include <stdio.h>
#include <math.h>

#define epsilon 0.00001

int main()
{
    double a, b;

    scanf("%lf %lf", &a, &b);
    
    double dif = fabs(a - b);

    if (dif < epsilon) {
        printf("EQ\n");
    } else {
        printf("NOT EQ\n");
    }

    return 0;
}
