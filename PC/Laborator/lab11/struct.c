#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student {
    char nume[40];
    int an;
    float medie;
} Student;

struct exemplu {
    int n;
    char *s;
};

int main()
{
    struct student stud1;
    strcpy(stud1.nume, "Maria");
    stud1.an = 2;
    stud1.medie = 9.5;

    Student *stud2 = (Student*) malloc(sizeof(Student));
    strcpy((*stud2).nume, "Popescu");
    stud2->an = 3;
    stud2->medie = 9.2;

    printf("stud1: %s %d %.2f\n", stud1.nume, stud1.an, stud1.medie);
    printf("stud2: %s %d %.2f\n", stud2->nume, stud2->an, stud2->medie);

    struct exemplu s1, s2;
    char *litere = "abcdef";
    s1.n = 5;
    s1.s = strdup(litere);
    s2 = s1;
    
    // printf("before\n");
    // printf("s1: %d %s\n", s1.n, s1.s);
    // printf("s2: %d %s\n", s2.n, s2.s);
    // s2.s[1] = 'x';
    // s2.n = 10;
    // printf("after\n");
    // printf("s1: %d %s\n", s1.n, s1.s);
    // printf("s2: %d %s\n", s2.n, s2.s);

    struct exemplu *p1;
    struct exemplu *p2;
    p1 = &s1;
    p2 = &s2;
    printf("before\n");
    printf("p1: %d %s\n", p1->n, p1->s);
    printf("p2: %d %s\n", p2->n, p2->s);
    p1->n = 10;
    p1->s[2] = 'w';
    printf("after\n");
    printf("p1: %d %s\n", p1->n, p1->s);
    printf("p2: %d %s\n", p2->n, p2->s);

    return 0;
}