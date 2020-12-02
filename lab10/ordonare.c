/**
 *  Exercitiul 1. Ordonare alfabetica cuvinte
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

void ordCresc(char* words[], int n) {
    printf("Inainte de sortare: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

    int i, j;
    char* aux = (char*)malloc(sizeof(N));
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            // daca se doreste dupa lungime se inlocuieste conditia cu strlen(words[i]) > strlen(words[j])
            if (strcmp(words[i], words[j]) > 0) {
                strcpy(aux, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], aux);
            }
        }
    }

    printf("Dupa sortare: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", words[i]);
    }
    printf("\n");

}

int main()
{
    char* words[20];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        words[i] = (char*) malloc(N * sizeof(char));
        scanf("%s", words[i]);
    }

    ordCresc(words, n);

    return 0;
}