#include <stdio.h>

int main()
{
    int n, m;
    float a[20][20];

    scanf("%d %d", &n, &m);
    // read matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%f", &a[i][j]);
        }
    }

    // print matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }

    return 0;
}
