#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define dmax 105

ifstream in("sume.in");
ofstream out("sume.out");

int A[dmax][dmax];
int N, M;

int s[dmax][dmax]; // s[i][j] = suma dreptunghiului cu coltul dreapta jos (i, j)
int Q;

int main(void) {

	in >> N >> M;
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			in >> A[i][j];
		}
	}

	// sume partiale
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			s[i][j] = A[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	}

	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= M; j++) {
			out << s[i][j] << " ";
		}
		out << '\n';
	}

	int x1, y1, x2, y2;

	in >> Q;
	for(int i = 0; i < Q; i++) {
		in >> x1 >> y1 >> x2 >> y2;

		int sum = s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
		out << sum << '\n';
	}

	return 0;
}