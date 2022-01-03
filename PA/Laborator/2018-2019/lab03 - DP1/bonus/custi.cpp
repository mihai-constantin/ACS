#include <iostream>
#include <fstream>
using namespace std;

ifstream in("custi.in");
ofstream out("custi.out");

#define dmax 1003

int st[dmax][dmax]; // st[i][j] = numarul de 1 consecutivi de pe linia i, aflati in stanga lui (i, j) inclusiv
int sus[dmax][dmax]; // sus[i][j] = numarul de 1 consecutivi de pe coloana j, aflati deasupra lui (i, j) inclusiv
int d[dmax][dmax]; // d[i][j] = latura maxima a unui patrat cu coltul dreapta jos (i, j)
int N;

int nr[dmax];

int main(void) {

	int x, i, j;

	in >> N;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			in >> x;
			if(x == 1) {
				st[i][j] = 1 + st[i][j - 1];
				sus[i][j] = 1 + sus[i - 1][j];
			}
			else {
				st[i][j] = 0;
				sus[i][j] = 0;
			}
		}
	}

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			// dinamica
			d[i][j] = min(st[i][j], sus[i][j]);
			d[i][j] = min(d[i][j], 1 + d[i - 1][j - 1]);

			nr[d[i][j]]++;
		}
	}

	for(i = N; i >= 1; i--) {
		nr[i] += nr[i + 1];
	}

	for(i = 1; i <= N; i++) {
		out << nr[i] << '\n';
	}


	return 0;
}