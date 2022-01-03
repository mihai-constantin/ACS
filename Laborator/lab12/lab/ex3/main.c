#include <stdio.h>

#define dim 101

typedef struct student {
    char nume[30];
    struct data_nastere {
        int zi;
        int luna;
        int an;
    } data_nastere;
    float medie;
} Student;

Student students[dim];

int main()
{
    char input_filename[] = "input.txt";
    FILE *in = fopen(input_filename, "rt");
    if (!in) {
        fprintf(stderr, "Can't open %s\n", input_filename);
        return -1;
    }

    int n, i;
    fscanf(in, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(in, "%s %d %d %d %f", students[i].nume, 
            &students[i].data_nastere.zi, &students[i].data_nastere.luna, &students[i].data_nastere.an,
            &students[i].medie);
    }
    fclose(in);

    char output_filename[] = "output.bin";
    FILE *out = fopen(output_filename, "wb");
    if (!out) {
        fprintf(stderr, "Can't  open %s\n", output_filename);
        return -1;
    }

    fwrite(students, sizeof(Student), n, out);
    fclose(out);

    // read binary file and print its output to console
    FILE *fin = fopen(output_filename, "rb");
    if (!fin) {
        fprintf(stderr, "Can't  open %s\n", output_filename);
        return -1;
    }

    Student students_from_file[dim];
    fread(students_from_file, sizeof(Student), n, fin);
    fclose(fin);

    printf("===== Data from binary file =====\n");
    for (i = 0; i < n; i++) {
        printf("%s %d %d %d %f\n", students_from_file[i].nume, 
            students_from_file[i].data_nastere.zi, students_from_file[i].data_nastere.luna, students_from_file[i].data_nastere.an,
            students_from_file[i].medie);
    }
    printf("\n");

    return 0;
}
