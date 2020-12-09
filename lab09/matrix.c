#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nl, nc, i, j;
    int **a;

    printf("nr linii = ");
    scanf("%d", &nl);

    printf("nr coloane = ");
    scanf("%d", &nc);

    a = (int**) malloc(nl * sizeof(int*));
    if (!a) {
        printf("malloc failed!");
        exit(-1);
    }

    for (i = 0; i < nl; i++) {
        a[i] = (int*) calloc(nc, sizeof(int));
        if (!a[i]) {
            printf("malloc failed!");
            exit(-1);
        }
    }

    printf("Componenete matrice: \n");
    for (i = 0; i < nl; i++) {
        for (j = 0; j < nc; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    printf("=== Afisare matrice =====\n");
    for (i = 0; i < nl; i++) {
        for (j = 0; j < nc; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < nl; i++) {
        free(a[i]);
    }
    free(a);
    return 0;
}