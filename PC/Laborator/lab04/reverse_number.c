/**
 * Exercitiul 4. 
 * Subprogram recursiv care inverseaza ordinea cifrelor unui numar intreg pozitiv
 */
#include <stdio.h>

int putere(int a, int b) {
    if (!b) {
        return 1;
    }
    return a * putere(a, b - 1);
}

int number_of_digits(int x) {
    if (x < 10) {
        return 1;
    }
    return 1 + number_of_digits(x/10);
}

/**
 *  r(123) = 321
 *  p(a, b) = a^b
 *  c(123) = 3
 *
 *  r(1234) = 4 * p(10, c(123)) + r(123) = 4 * p(10, 3) + r(123) = 4000 + r(123) = 4000 + 321 = 4321
 *  r(123) = 3 * p(10, c(12)) + r(12) = 300 + r(12) = 300 + 21 = 321
 *  r(12) = 2 * p(10, c(1)) + r(1) = 20 + r(1) = 20 + 1 = 21
 *  r(1) = 1 
 * 
 */
int reverse_number(int x) {
    if (x < 10) {
        return x;
    }
    return (x % 10) * putere(10, number_of_digits(x / 10)) + reverse_number(x / 10);
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("reverse_number: %d\n", reverse_number(x));

    return 0;
}
