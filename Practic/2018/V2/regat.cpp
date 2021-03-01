#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int dlin[4] = {-1, 0, 1, 0};
const int dcol[4] = {0, 1, 0, -1};

typedef struct Elem {
	int lin;
	int col;
} Elem;

ifstream in("in");

#define dmax 1005

int A[dmax][dmax];
int P, N, M;

bool visited[dmax][dmax];
int nr;

void FILL(Elem x, int culoare) {

	Elem y;

	if(A[x.lin][x.col] == culoare) {
		nr++;
		visited[x.lin][x.col] = true;

		for(int k = 0; k < 4; k++) {
			y.lin = x.lin + dlin[k];
			y.col = x.col + dcol[k];

			if(y.lin >= 1 && y.lin <= N && y.col >= 1 && y.col <= M && A[y.lin][y.col] == culoare && !visited[y.lin][y.col]) {
				FILL(y, culoare);
			}
		}
	}
}

void initialize() {
	int i, j;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			visited[i][j] = false;
		}
	}
}

int main() {
	/* Cititi de la STDIN si afisati la STDOUT. Decomentati linia de mai jos daca
     * folositi cin/cout. Nu imbinati cin/cout cu scanf/printf in acest caz.
     */
	// ios::sync_with_stdio(false);

	int i, j, k, aux, xfin, yfin;

	in >> P;
	in >> N >> M;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			in >> A[i][j];
		}
	}

	Elem S, y;
	int answer = -1;

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {

			S.lin = i;
			S.col = j;

			// parcurg vecinii lui S
			for(k = 0; k < 4; k++) {
				y.lin = S.lin + dlin[k];
				y.col = S.col + dcol[k];

				if(y.lin >= 1 && y.lin <= N && y.col >= 1 && y.col <= M 
						&& A[y.lin][y.col] != A[S.lin][S.col]) {

					// punem pe pozitia vecinului valoarea celului de la pozitia (i, j)
					// printf("A[%d][%d] <- %d\n", y.lin, y.col, A[S.lin][S.col]);
					aux = A[y.lin][y.col];
					A[y.lin][y.col] = A[S.lin][S.col];
					nr = 0;
					initialize();
					FILL(S, A[S.lin][S.col]);
					A[y.lin][y.col] = aux;

					// printf("nr: %d\n", nr);

					if(answer < nr) {
						answer = nr;
						xfin = y.lin;
						yfin = y.col;
					}
				}
			}
		}
	}

	cout << answer << " " << xfin - 1 << " " << yfin - 1 << '\n';

    return 0;
}