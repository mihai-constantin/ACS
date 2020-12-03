/**
 *  Exercitiul 3 + 4. Folosire strtok 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

int main()
{
    int nr = 0;

    char *s = (char*) malloc(N * sizeof(char)); // sirul citit
    char *my_word = (char*) malloc(N * sizeof(char)); // cuvantul pe care il caut in sir

    fgets(s, N, stdin);
    s[strlen(s) - 1] = '\0'; // scap de enter

    fgets(my_word, N, stdin);
    my_word[strlen(my_word) - 1] = '\0';

    const char* delims = " .,;?!";
    char *word = strtok(s, delims);
    printf("Cuvintele din propozitie: ");
    while(word != NULL) {
        printf("%s ", word);
        if (!strcmp(word, my_word)) {
            nr++;
        }
        // deplasare la cuvantul urmator
        word = strtok(NULL, delims);
    }
    printf("\n");
    printf("nr: %d\n", nr);

    return 0;
}