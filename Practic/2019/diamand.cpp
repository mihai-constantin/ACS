#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

ifstream in("in");

const int dlin[4] = {-1, 0, 1, 0};
const int dcol[4] = {0, 1, 0, -1};

#define dmax 1005

typedef struct Elem {
	int lin;
	int col;
} Elem;

int A[dmax][dmax];
int N, M, P, L, C;

int d[dmax][dmax];
queue <Elem> q;

void Lee(Elem S) {

	int k;
	Elem x, y;

	// introduc in coada nodul de start
	q.push(S);
	d[S.lin][S.col] = 0;

	while(!q.empty()) {
		x = q.front();
		q.pop();

		// parcurg vecinii y ai lui x
		for(k = 0; k < 4; k++) {
			y.lin = x.lin + dlin[k];
			y.col = x.col + dcol[k];

			if(y.lin >= 1 && y.lin <= N && y.col >= 1 && y.col <= M && d[y.lin][y.col] > 1 + d[x.lin][x.col]) {
				d[y.lin][y.col] = 1 + d[x.lin][x.col];
				q.push(y);
			}
		}
	}

}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

	int i, j;

	in >> N >> M; // dimensiune matrice
	in >> P; // numar maxim mutari
	in >> L >> C;

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			in >> A[i][j];
		}
	}

	Elem S;
	S.lin = L;
	S.col = C;

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			d[i][j] = N * M + 1;
		}
	}

	Lee(S);

	// for(i = 1; i <= N; i++) {
	// 	for(j = 1; j <= M; j++) {
	// 		cout << d[i][j] << " ";
	// 	}
	// 	cout << '\n';
	// }

	bool gasit = false;
	int maxim;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			if(d[i][j] <= P) {

				// am un posibil candidat
				if(gasit == false) {
					gasit = true;
					maxim = A[i][j];
				}
				else {
					if(A[i][j] > maxim) {
						maxim = A[i][j];
					}
				}
			}
		}
	}

	cout << maxim << '\n';

    return 0;
}