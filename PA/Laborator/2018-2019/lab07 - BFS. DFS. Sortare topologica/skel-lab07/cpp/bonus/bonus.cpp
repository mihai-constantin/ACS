#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef struct Elem {
	int lin;
	int col;
}Elem;

#define dmax 1000
#define INF 2000000005

const int d_lin[4] = {-1, 0, 1, 0};
const int d_col[4] = {0, 1, 0, -1};

int A[dmax][dmax];
// d[i][j] = distanta minima de la nodul de start la celula (i, j)
int d[dmax][dmax];
queue <Elem> q;
int length;
int N;

FILE *in, *out;

void drum(Elem node) {

	if(d[node.lin][node.col] == 0) {
		printf("(%d %d) -> ", node.lin, node.col);
		return;
	}

	Elem y;
	// parcurg vecinii nodului node
	for(int k = 0; k < 4; k++) {
		y.lin = node.lin + d_lin[k];
		y.col = node.col + d_col[k];

		if(y.lin >= 1 && y.lin <= N && y.col >= 1 && y.col <= N 
			&& d[y.lin][y.col] + 1 == d[node.lin][node.col]) {
			drum(y);
		}
	}

	if(d[node.lin][node.col] == length) {
		printf("(%d %d)", node.lin, node.col);
	}
	else {
		printf("(%d %d) -> ", node.lin, node.col);
	}
}

int main()
{
	in = fopen("bonus.in", "r");
	out = fopen("bonus.out", "w");

	int x, y, i, j, k;

	fscanf(in, "%d", &N);
	fscanf(in, "%d %d", &x, &y);

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			fscanf(in, "%d", &A[i][j]);
		}
	}

	printf("--- A ---\n");
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// initializare matrice d
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			d[i][j] = INF;
		}
	}

	// introduc in coada nodul de start
	Elem S;
	S.lin = x;
	S.col = y;
	q.push(S);
	d[S.lin][S.col] = 0;

	while(!q.empty()) {
		Elem node = q.front();
		q.pop();

		// parcurg vecinii nodului node
		Elem y1;
		for(k = 0; k < 4; k++) {
			y1.lin = node.lin + d_lin[k];
			y1.col = node.col + d_col[k];

			if(y1.lin >= 1 && y1.lin <= N && y1.col >= 1 && y1.col <= N 
				&& A[y1.lin][y1.col] != 1) {
				// ma intreb daca pot optimiza distanta
				if(d[y1.lin][y1.col] > 1 + d[node.lin][node.col]) {
					d[y1.lin][y1.col] = 1 + d[node.lin][node.col];
					q.push(y1);
				}
			}
		}
	}

	printf("--- d ---\n");
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			if(d[i][j] == INF) {
				d[i][j] = -1;
			}
			printf("%d ", d[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	bool ok = false;
	int xf, yf;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			if(A[i][j] == 2) {
				if(d[i][j] != -1) {
					if(ok == false) {
						ok = true;
						length = d[i][j];
						xf = i;
						yf = j;
					}
					else {
						if(length > d[i][j]) {
							length = d[i][j];
							xf = i;
							yf = j;
						}
					}
				}
			}
		}
	}

	printf("length = %d\n", length);
	printf("(xf, yf) = %d %d\n", xf, yf);
	Elem Sf;
	Sf.lin = xf;
	Sf.col = yf;

	drum(Sf);
	printf("\n");

	return 0;
}