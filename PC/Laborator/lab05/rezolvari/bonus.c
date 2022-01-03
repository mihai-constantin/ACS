/**
 *  Bonus
 *  Adunarea a doua numere mari.
 *  Pentru detalii suplimentare: https://www.infoarena.ro/lucrul-cu-nr-mari
 */
#include <stdio.h>

#define N 1000000

void atrib_value(int A[N], unsigned long x) {
    A[0] = 0;
    while(x) {
        A[0]++; // incrementam numarul de cifre ale lui x
        A[A[0]] = x % 10;
        x /= 10;
    }
}

void add(int A[N], int B[N]) {
    // A <- A + B
    int i, T = 0;

    // in functie de care numar este mai mare, il adaptam pe celalalt
    if (B[0] > A[0]) {
        for (i = A[0] + 1; i <= B[0]; i++) {
            A[i] = 0;
        }
        A[0] = B[0];
    } else {
        for (i = B[0] + 1; i <= A[0]; i++) {
            B[i] = 0;
        }
        B[0] = A[0];
    }

    for (i = 1; i <= A[0]; i++) {
        A[i] += B[i] + T;
        T = A[i]/10;
        A[i] %= 10;
    }
    if (T) {
        A[++A[0]] = T;
    }
}

void print_array(int H[N]) {
    for (int i = 0; i <= H[0]; i++) {
        printf("%d ", H[i]);
    }
    printf("\n");
}

int main()
{
    int A[N], B[N];
    unsigned long x, y;
    scanf("%ld %ld", &x, &y);
    atrib_value(A, x);
    atrib_value(B, y);

    printf("A: ");
    print_array(A);
    printf("B: ");
    print_array(B);

    add(A, B);
    printf("A + B: ");
    print_array(A);

    return 0;
}
