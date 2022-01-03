#include <stdio.h>
#include <stdlib.h>

#define dim 101

int main()
{
    char input_filename[] = "data.in";
    FILE *in = fopen(input_filename, "rt");
    if (!in) {
        fprintf(stderr, "Error: Can't open file %s\n", input_filename);
        return -1;
    }

    int n, v[dim], i;

    fscanf(in, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(in, "%d", &v[i]);
    }
    fclose(in);

    for(i = 0; i < dim; i++) {
        v[i] *= 2;
    }

    char output_filename[] = "data.out";
    FILE *out = fopen(output_filename, "wt");
    if (!out) {
        fprintf(stderr, "Error: Can't open file %s\n", output_filename);
        return -1;
    }

    fprintf(out, "%d\n", n);
    for(i = 0; i < n; i++) {
        fprintf(out, "%d ", v[i]);
    }
    fprintf(out, "\n");

    fclose(out);

    return 0;
}