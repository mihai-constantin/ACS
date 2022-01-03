#include <stdio.h>

#define dim 101

int main()
{
    char input_filename[] = "data.in";

    FILE *in = fopen(input_filename, "rb");
    if (!in) {
        fprintf(stderr, "Error: Can't open file %s\n", input_filename);
        return -1;
    }

    int n, v[dim], i;
    
    fread(&n, sizeof(int), 1, in);
    fread(v, sizeof(int), n, in);

    fclose(in);

    for(i = 0; i < n; i++) {
        v[i] *= 2;
    }

    char output_filename[] = "data.out";
    FILE *out = fopen(output_filename, "wb");
    if (!out) {
        fprintf(stderr, "Error: Can't open file %s\n", output_filename);
        return -1;
    }

    fwrite(&n, sizeof(int), 1, out);
    fwrite(v, sizeof(int), n, out);

    fclose(out);

    return 0;
}
