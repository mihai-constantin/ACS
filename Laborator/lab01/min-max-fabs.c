/**
 * Exercitiul 6. 
 * Determinarea minimului, respectiv maximului dintre 2 numere folosind fabs.
 */
#include <stdio.h>
#include <math.h>

int main()
{
    double a, b;

    scanf("%lf %lf", &a, &b);
    
    double maxim = (a + b + fabs(a - b)) / 2;
    double minim = (a + b - fabs(a - b)) / 2;

    printf("minim: %g\n", minim);
    printf("maxim: %g\n", maxim);

    return 0;
}
