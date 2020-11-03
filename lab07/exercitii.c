/**
 * Exercitiile 0 - 4 laborator
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int is_even(int n) {
    return (n&1) == 0;
}

int pow2(int n) {
    return (1 << n);
}

// reprezentare numar in complement data de 2
int flip_bits(int n) {
    return ~n;
}

int invert_bits(int n) {
    int x = log2(n) + 1;
    for (int i = 0; i < x; i++) {
        n = (n ^ (1 << i));
    }
    return n;
}

void print_bits(int n) {
    int x = log2(n) + 1;
    for (int i = x - 1; i >= 0; i--) {
        if (!(n & (1 << i))) {
            printf("0");
        } else {
            printf("1");
        }
    }
    printf("\n");
}

bool is_power2(int n) {
    int x = log2(n) + 1;
    for (int i = x - 2; i >= 0; i--) {
        if ((n & (1 << i))) {
            return false;
        }
    }
    return true;
}

int main() 
{
    int n;
    scanf("%d", &n);
    printf("is_even: %d\n", is_even(n));
    printf("pow2: %d\n", pow2(n));
    printf("flip_bits: %d\n", flip_bits(n));
    printf("invert_bits: %d\n", invert_bits(n));
    print_bits(n);
    printf("is_power2: %d\n", is_power2(n));

    return 0;
}
