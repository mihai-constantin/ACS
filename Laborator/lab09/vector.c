#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i;
    int *a;

    printf("n = ");
    scanf("%d", &n); // dimensiune vector

    a = (int*) calloc(n, sizeof(int));
    printf("Componente vector: \n");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    free(a);
    return 0;
}