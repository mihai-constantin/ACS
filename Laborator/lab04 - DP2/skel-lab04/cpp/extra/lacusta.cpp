#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

ifstream in("lacusta.in");
ofstream out("lacusta.out");

#define dmax 255
#define INF dmax * dmax

int A[dmax][dmax];
int d[dmax][dmax];
int n, m;

int main(void) {

	in >> n >> m;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			in >> A[i][j];
		}
	}

	for(int j = 0; j < m; j++) {
		d[0][j] = INF;
		d[1][j] = A[0][0] + A[0][j] + A[1][j];
	}

	d[1][0] = INF;

	int min1, min2, col_min1, col_min2;

	for(int i = 1; i < n - 1; i++) {

		min1 = d[i][0];
		col_min1 = 0;

		min2 = d[i][1];
		col_min2 = 1;

		if(min1 > min2) {
			swap(min1, min2);
			swap(col_min1, col_min2);
		}

		for(int j = 2; j < m; j++) {
			if(d[i][j] < min1) {
				min2 = min1;
				col_min2 = col_min1;
				min1 = d[i][j];
				col_min1 = j;
			}
			else {
				if(d[i][j] < min2) {
					min2 = d[i][j];
					col_min2 = j;
				}
			}
		}

		for(int j = 0; j < m; j++) {
			if(j != col_min1) {
				d[i + 1][j] = min1 + A[i][j] + A[i + 1][j];
			} 
			else {
				d[i + 1][j] = min2 + A[i][j] + A[i + 1][j];

			}
		}
	}

	int min = d[n - 1][0];
	int col = 0;
	for(int j = 1; j < m - 1; j++) {
		if(d[n - 1][j] < min) {
			min = d[n - 1][j];
			col = j;
		}
	}

	out << min + A[n - 1][m - 1] << '\n';

	return 0;
}