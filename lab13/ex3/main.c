#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define SQUARE(a) (a) * (a)
#define SQUARE(a) ((a) * (a))

// #define MAX(a, b) a > b ? a : b
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define SWAP(type, x, y) {\
    type tmp = x; \
    x = y; \
    y = tmp; \
}

int main(int argc, char const *argv[])
{
    printf("~SQUARE(2): %d\n", ~SQUARE(2));
    printf("~(2)*(2): %d\n", ~(2)*(2));
    printf("~4: %d\n", ~4);

    printf("max = %d\n", 1 << MAX(19 + 1, 10 + 1));

    int x = 1, y = 2;
    printf("[BEFORE] x: %d y: %d\n", x, y);
    SWAP(int, x, y);
    printf("[AFTER] x: %d y: %d\n", x, y);

    char *p = strdup("A");
    char *q = strdup("B");
    printf("[BEFORE] p: %s q: %s\n", p, q);
    SWAP(char*, p, q);
    printf("[AFTER] p: %s q: %s\n", p, q);

    free(p);
    free(q);

    return 0;
}
