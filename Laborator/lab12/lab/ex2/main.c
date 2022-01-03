#include <stdio.h>

int main()
{
    char input_filename[] = "data.bin";
    FILE *in = fopen(input_filename, "rb");
    if (!in) {
        fprintf(stderr, "Can't open %s\n", input_filename);
        return -1;
    }

    char output_filename[] = "data.txt";
    FILE *out = fopen(output_filename, "wt");
    if (!out) {
        fprintf(stderr, "Can't open %s\n", output_filename);
        return -1;
    }

    int x;
    long int s = 0;
    while(!feof(in)) {
        size_t ret = fread(&x, sizeof(int), 1, in);
        if (ret == 1) {
            printf("%d ", x);
            if (x % 2 == 1) {
                s += x;
            } else {
                fprintf(out, "%d ", x);
            }
        }
    } 
    printf("\n");
    printf("s: %ld\n", s);

    fclose(in);
    fclose(out);

    return 0;
}
