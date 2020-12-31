#include <stdio.h>
#include <stdarg.h>

void list_ints(int first, ...) {
    if (first < 0) {
        printf("No numbers\n");
        return;
    }

    /* declarare lista parametri */
    va_list args;

    /* initializare lista parametri */
    va_start(args, first);

    int current = first;
    while(current >= 0) {
        printf("%d ", current);
        /* accesare parametru urmator */
        current = va_arg(args, int);
    }
    printf("\n");

    /* curatare lista parametri */
    va_end(args);
}

int main(int argc, char const *argv[])
{
    list_ints(-1);
    list_ints(128, 512, 768, 4096, -1);
    list_ints('a', 'b', 0xa, 0xb, -2);
    list_ints(1, -1);
    list_ints(1, 2, 3, -1, 1, 2, 3);

    return 0;
}
