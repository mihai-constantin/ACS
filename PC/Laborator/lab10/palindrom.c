/**
 *  Exercitiul 2. Determinare propozitie palindrom
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

int main()
{
    int i, j, idx = 0;

    char *s = (char*) calloc(N, sizeof(char));
    fgets(s, N, stdin);
    s[strlen(s) - 1] = '\0'; // scap de enter

    for (i = 0; i < strlen(s); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 32;
        }
        if (s[i] != ' ') {
            s[idx++] = s[i];
        }
    }
    s[idx] = '\0';

    int length = strlen(s);
    for (i = 0, j = length - 1; i < length/2; i++, j--) {
        if (s[i] != s[j]) {
            printf("0\n");
            return 0;
        }
    }

    printf("1\n");

    return 0;
}