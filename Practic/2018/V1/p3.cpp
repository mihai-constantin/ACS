#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

#define Nmax 1000005

typedef struct Elem {
	int lin;
	int col;
} Elem;

const int dlin[4] = {-1, 0, 1, 0};
const int dcol[4] = {0, 1, 0, -1};

int A[3][Nmax];
int M;

int d[3][Nmax];
queue <Elem> q;

void Lee(Elem node) {

	int k;
	Elem x, y;

	// introduc in coada nodul de start
	q.push(node);
	d[node.lin][node.col] = A[node.lin][node.col];

	while(!q.empty()) {
		x = q.front();
		q.pop();

		// parcurg vecinii y ai lui x
		for(k = 0; k < 4; k++) {
			y.lin = x.lin + dlin[k];
			y.col = x.col + dcol[k];

			if(y.lin >= 1 && y.lin <= 2 && y.col >= 1 && y.col <= M && A[y.lin][y.col] != -1) {
				if((d[y.lin][y.col] > d[x.lin][x.col] + A[y.lin][y.col]) || d[y.lin][y.col] == -2) {
					d[y.lin][y.col] = d[x.lin][x.col] + A[y.lin][y.col];
					q.push(y);
				}
			}
		}

	}

}

int main() {
	/* Cititi de la STDIN si afisati la STDOUT. Decomentati linia de mai jos daca
     * folositi cin/cout. Nu imbinati cin/cout cu scanf/printf in acest caz.
     */
	// ios::sync_with_stdio(false);

	int i, j;

	scanf("%d", &M);
	for(i = 1; i <= 2; i++) {
		for(j = 1; j <= M; j++) {
			d[i][j] = -2;
			scanf("%d", &A[i][j]);
		}
	}

	Elem S;
	S.lin = S.col = 1;
	Lee(S);

	printf("%d\n", A[2][M]);

    return 0;
}