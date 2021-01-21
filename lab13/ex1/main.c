#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Usage: ./main <x> <y>\n");
        exit(-1);
    }

    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    // int x = atoi(argv[1]);
    // printf("x = %d\n", x);
    return 0;
}
