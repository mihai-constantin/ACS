/**
 * Exercitiul 2
 * Functii specifice siruri de caractere
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_length(char *s) {
    return strlen(s);
}

char* strdel(char *s, int pos, int n) {
    char* substr = (char*) malloc(strlen(s) * sizeof(char));
    strncpy(substr, s, pos);
    strcat(substr, s + pos + n);
    return substr;
}

char* strins(char *s1, int pos, char *s2) {
    int length_s1 = str_length(s1);
    int length_s2 = str_length(s2);
    char* aux = (char*) malloc((length_s1 + length_s2) * sizeof(char));
    strcpy(aux, s1);
    for (int i = length_s1 - 1; i >= pos; i--) {
        aux[i + length_s2] = s1[i];
    }
    for (int i = pos; i < pos + length_s2; i++) {
        aux[i] = s2[i - pos];
    }
    aux[length_s1 + length_s2] = '\0';
    return aux;
}

int eq_mask(char *sir, char *masca) {
    int length = str_length(sir);
    for (int i = 0; i < length; i++) {
        if (sir[i] != masca[i] && masca[i] != '?') {
            return 0;
        }
    }
    return 1;
}

int eqcuv(char *cuv, char **tablou, int n) {
    for (int i = 0; i < n; i++) {
        if (!strcmp(cuv, tablou[i])) {
            return 1;
        }
    }
    return 0;
}

int main()
{
    char* s1 = "abcdefg";
    printf("length: %d\n", str_length(s1));

    char* s2 = strdel(s1, 2, 3);
    printf("s2: %s\n", s2);

    char* s3 = strins(s1, 2, "xyz");
    printf("s3: %s\n", s3);

    printf("eq_mask: %d\n", eq_mask("abcde", "?bc?e"));

    char *tablou[100] = {"curs1", "curs2", "curs3"};
	char *cuv1 = "curs2", *cuv2 = "curs5";
	printf("curs2 %s in tablou\n", (eqcuv(cuv1, tablou, 3)) ? "este" : "nu este");
	printf("curs5 %s in tablou\n", (eqcuv(cuv2, tablou, 3)) ? "este" : "nu este");

    return 0;
}
