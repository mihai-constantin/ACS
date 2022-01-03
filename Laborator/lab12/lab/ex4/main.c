#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 30

typedef struct student {
    char *nume;
    struct data_nastere {
        int zi;
        int luna;
        int an;
    } data_nastere;
    float medie;
} Student;

Student *students;

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
    students = (Student*) malloc(n * sizeof(Student));
    for (i = 0; i < n; i++) {
        students[i].nume = (char*) malloc(NAME_LENGTH * sizeof(char));
        fscanf(in, "%s %d %d %d %f", students[i].nume, 
            &students[i].data_nastere.zi, &students[i].data_nastere.luna, &students[i].data_nastere.an,
            &students[i].medie);
    }
    fclose(in);
   
    printf("===== Data from text file =====\n");
    for (i = 0; i < n; i++) {
        printf("%s %d %d %d %f\n", students[i].nume, 
            students[i].data_nastere.zi, students[i].data_nastere.luna, students[i].data_nastere.an,
            students[i].medie);
    }
    printf("\n");

    char output_filename[] = "output.bin";
    FILE *out = fopen(output_filename, "wb");
    if (!out) {
        fprintf(stderr, "Can't  open %s\n", output_filename);
        return -1;
    }

    for (i = 0; i < n; i++) {
        fwrite(students[i].nume, sizeof(char), strlen(students[i].nume), out);
        fwrite(&students[i].data_nastere, sizeof(struct data_nastere), 1, out);
        fwrite(&students[i].medie, sizeof(float), 1, out);
    }

    fclose(out);

    // read binary file and print its output to console
    FILE *fin = fopen(output_filename, "rb");
    if (!fin) {
        fprintf(stderr, "Can't  open %s\n", output_filename);
        return -1;
    }

    Student *students_from_file = (Student*) malloc(n * sizeof(Student));
    for (i = 0; i < n; i++) {
        students_from_file[i].nume = (char*) malloc((strlen(students[i].nume) + 1) * sizeof(char));
        fread(students_from_file[i].nume, sizeof(char), strlen(students[i].nume), fin);
        students_from_file[i].nume[strlen(students[i].nume)] = '\0';
        fread(&students_from_file[i].data_nastere, sizeof(struct data_nastere), 1, fin);
        fread(&students_from_file[i].medie, sizeof(float), 1, fin);
    }
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
