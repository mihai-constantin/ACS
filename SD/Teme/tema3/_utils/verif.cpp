/* Copyright 2018
 * Neatu Darius-Florentin <neatudarius@gmail.com>
 * Edited by Stefania Budulan <stefaniabudulan@yahoo.com>
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

#define BONUS "bonus.out"
#define MAX_CHRS 1000

void DIE(float points, const char *msg) {
	FILE *f;

	f = fopen("score.verif", "wt");
	fprintf(f, "%.1f", points);
	fclose(f);

	f = fopen("output.verif", "wt");
	fprintf(f, "%s", msg);
	fclose(f);

	exit(0);
}

int is_useful_char(char c) {
	return (c >= '0' && c <= '9') || c == '=' || c == '+';
}

void wrong_answer_atchars(char src, char dst) {
	char c[100];

	#ifdef ONLINE_JUDGE
	sprintf(c, "WA ");
	#else
	sprintf(c, "WA %c vs %c", src, dst);
	#endif

	DIE(0, c);
}

int main(int argc, char **argv) {
	if(argc != 3) {
		DIE(0, "Usage ./verif problem_name test_points");
	}

	char name[100];
	strcpy(name, argv[1]);
	strcat(name, ".out");

	float points = atof(argv[2]);

	FILE *file_out = fopen(name, "rt"),
		 *file_ref = fopen("res.ok", "rt");

	if(file_ref == NULL) {
		DIE(0, "Nu exista fisierul de referinta");
	}

	if(file_out == NULL) {
		DIE(0, "Nu exista fisier de output");
	}

	int for_last = strcmp(name, BONUS);

	// Treat separately last problem
	if(for_last == 0) {
		char line_ref[MAX_CHRS], line_out[MAX_CHRS];
		if (fgets(line_ref, MAX_CHRS, file_ref)) {
			int len_ref = strlen(line_ref);
			if (fgets(line_out, MAX_CHRS, file_out)) {
				int len_out = strlen(line_out);
				int i = 0;
				while((i < len_ref && i < len_out) &&
						is_useful_char(line_ref[i])) {
					if(line_ref[i] != line_out[i]) {
						wrong_answer_atchars(line_ref[i], line_out[i]);
					}
					i++;
				}

				int right_answer = 0;
				// Test if the output is longer or shorter than the refrence
				if(i < len_ref && is_useful_char(line_ref[i]))
					wrong_answer_atchars(line_ref[i], ' ');
				if (i < len_out && is_useful_char(line_out[i]))
					wrong_answer_atchars(' ', line_out[i]);
				// Everything checks out
				DIE(points, "OK ");
				return 0;

			} else {
				DIE(0, "Fisierul de iesire nu contine un numar corespunzator de linii");
			}
		}
	}

	long long int answer_out, answer_ref;
	while(fscanf(file_ref, "%lld", &answer_ref) == 1) {
		int ret = fscanf(file_out, "%lld", &answer_out);
		if(ret < 0) {
			DIE(0, "Fisierul de iesire nu contine un numar corespunzator de numere");
		}

		if(answer_ref != answer_out) {
			char c[100];

			#ifdef ONLINE_JUDGE
			sprintf(c, "WA ");
			#else
			sprintf(c, "WA %lld vs %lld", answer_out, answer_ref);
			#endif

			DIE(0, c);
		}
	}


	DIE(points, "OK ");

	return 0;
}
