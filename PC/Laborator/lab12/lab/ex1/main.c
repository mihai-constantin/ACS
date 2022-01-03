#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n, i, x;
    scanf("%d", &n);

    char filename[] = "data.bin";
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Can't open %s\n", filename);
    }

    // fwrite(&n, sizeof(int), 1, fp);

    srand(time(0));
    for (i = 0; i < n; i++) {
        x = rand();
        printf("%d ", x);
        fwrite(&x, sizeof(int), 1, fp);
    }

    printf("\n");
    fclose(fp);

    return 0;
}
