/**
 * Exercitiul 3. 
 * Subprogram recursiv care returneaza numarul de cifre al unui numar primit ca parametru.
 */
#include <stdio.h>

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
