#include <stdio.h>

int sizeof_file(char *filename) {
    FILE *in = fopen(filename, "rt");
    if (!in) {
        return -1;
    }

    fseek(in, 0, SEEK_END);
    int bytes = ftell(in);
    fclose(in);
    return bytes;
}

int main()
{
    char filename[] = "data.in";

    int file_size = sizeof_file(filename);
    if (file_size < 0) {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        return -1;
    }

    printf("file_size: %d bytes\n", file_size);

    return 0;
}
