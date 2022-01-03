/**
 * Exercitiul 3. 
 * Subprogram recursiv care returneaza numarul de cifre al unui numar primit ca parametru.
 */
#include <stdio.h>

/**
 *  f(1234) = 1 + f(123) = 1 + 1 + 1 + 1 = 4
 *  f(123) = 1 + f(12) = 1 + 1 + 1 = 3
 *  f(12) = 1 + f(1) = 1 + 1 = 2
 *  f(1) = 1
 */
int number_of_digits(int x) {
    if (x < 10) {
        return 1;
    }
    return 1 + number_of_digits(x/10);
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("number_of_digits: %d\n", number_of_digits(x));

    return 0;
}
