/**
 * Algoritmul de inmultire secventiala de matrici
 * C <- A * B
 */
#include <stdio.h>

#define dmax 100

int A[dmax][dmax];
int B[dmax][dmax];
int C[dmax][dmax];
int n;

void read() {
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }
}

void multiply() {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void print() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    read();
    multiply();
    print();

    return 0;
}