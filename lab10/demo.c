#include <stdio.h>
#include <string.h>

#define N 100

int main()
{
    char a[N];

    char *b="unsir";
    for (int i = 0; i < strlen(b); i++) {
        printf("%c", b[i]);
        // b[i] = 'a'; seg. fault (nu avem drept de scriere)
    }
    printf("\n");

    char *c; // neinitializat

    char s[N];
    // gets(s);
    fgets(s, N, stdin); // retine si enter-ul
    s[strlen(s) - 1] = '\0'; // scap de enter
    printf("s: ");
    puts(s);

    printf("length: %ld\n", strlen(s));

    // strcpy
    strncpy(a, s, 1);
    printf("a: %s\n", a);
    strcpy(a, s);
    printf("a: %s\n", a);

    // strcat
    strcat(a, " are mere ");
    printf("a: %s\n", a);
    strncat(a, "si pere si prune", 7);
    printf("a: %s\n", a);

    // strcmp
    printf("strcmp(ana, maria) = %d\n", strcmp("ana", "maria"));
    printf("strcmp(maria, ana) = %d\n", strcmp("maria", "ana"));
    printf("strcmp(ana, ana) = %d\n", strcmp("ana", "ana"));

    // strchr
    c = strchr(s, 'n');
    if (c == NULL) {
        printf("Caracterul nu apare in sirul s\n");
    } else {
        printf("%s\n", c);
    }

    // strstr
    char* d = strstr(s, "na");
    if (d == NULL) {
        printf("Substring-ul nu apare in sirul s\n");
    } else {
        printf("%s\n", d);
    }

    return 0;
}