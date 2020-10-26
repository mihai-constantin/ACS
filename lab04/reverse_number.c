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
