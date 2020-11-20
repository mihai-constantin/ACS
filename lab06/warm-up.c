#include <stdio.h>

#define N 100

void read_matrix(int matrix[N][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}
int sum(int matrix[N][N], int n) {
    // suma elementelor de deasupra diagonalei principale
    int s = 0;
    for(int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            s += matrix[i][j];
            // printf("%d ", matrix[i][j]);
        }
    }
    // printf("\n");
    return s;
}

void transpose_matrix(int matrix[N][N], int n) {
    int aux;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            aux = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = aux;
        }
    }
}

void print_matrix(int matrix[N][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_elemets(int matrix[N][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j >= n - 1) {
                printf("%d ", matrix[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

int main()
{
    int n;
    int matrix[N][N];

    scanf("%d", &n);
    read_matrix(matrix, n);
    printf("-----   INITIAL MATRIX  -----\n");
    print_matrix(matrix, n);
    printf("Sum of upper principal diagonal elements: %d\n", sum(matrix, n));
    printf("-----   Elemente de sub diagonala secundara -----\n");
    print_elemets(matrix, n);
    transpose_matrix(matrix, n);
    printf("-----   TRANSPOSE MATRIX  -----\n");
    print_matrix(matrix, n);

    return 0;
}
