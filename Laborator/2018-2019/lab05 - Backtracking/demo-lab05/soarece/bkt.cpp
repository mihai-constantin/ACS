#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define dmax 15

struct node {
	int lin;
	int col;
};

int dlin[2] = {0, 1};
int dcol[2] = {1, 0};

int mat[dmax][dmax];
int N;

node sol[dmax * dmax];

void write(int k) {

	for(int i = 0; i < k; i++) {
		printf("(%d %d) ", sol[i].lin, sol[i].col);
	}
	printf("\n");
}

bool valid(int x, int y) {
	if(x >= 0 && x < N && y >=0 && y < N) {
		return true;
	}
	return false;
}

void bkt(int x, int y, int p) {

	if(x == N - 1 && y == N - 1) {
		// am gasit o solutie
		write(p);
		return;
	}

	if(valid(x, y)) {
		for(int i = 0; i < 2; i++) {
			int x1 = x + dlin[i];
			int y1 = y + dcol[i];

			if(valid(x1, y1) && mat[x1][y1] == 0) {
				// adaug solutia
				sol[p].lin = x1;
				sol[p].col = y1;
				bkt(x1, y1, p + 1);
			}
		}
	}

}

int main(void) {

	freopen("in", "r", stdin);
	freopen("out", "w", stdout);

	scanf("%d", &N);
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf("%d", &mat[i][j]);
		}
	}

	node n;
	n.lin = 0;
	n.col = 0;
	sol[0] = n;

	bkt(0, 0, 1);
}