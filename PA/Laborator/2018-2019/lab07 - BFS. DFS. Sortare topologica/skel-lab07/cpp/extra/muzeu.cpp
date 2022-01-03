#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;

#define dmax 255
#define INF 100005

typedef struct Elem {
	int lin;
	int col;
}Elem;

const int d_lin[4] = {-1, 0, 1, 0};
const int d_col[4] = {0, 1, 0, -1};

int A[dmax][dmax];
queue<Elem> q;

int N;

void BFS(Elem S) {

	int k;
	Elem x, y;

	// introduc in coada nodul de start
	q.push(S);
	A[S.lin][S.col] = 0;

	while(!q.empty()) {
		x = q.front();
		q.pop();

		// parcurg vecinii y ai lui x
		for(k = 0; k < 4; k++) {
			y.lin = x.lin + d_lin[k];
			y.col = x.col + d_col[k];

			if(y.lin >= 1 && y.lin <= N && y.col >= 1 && y.col <= N 
				&& A[y.lin][y.col] > A[x.lin][x.col] + 1) {
				A[y.lin][y.col] = 1 + A[x.lin][x.col];
				q.push(y);
			}
		}
	}
}

int main()
{
	freopen("muzeu.in", "r", stdin);
	freopen("muzeu.out", "w", stdout);

	int i, j;
	char c;

	cin >> N;

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			cin >> c;
			switch(c) {
				case 'P':
					A[i][j] = 0;
					break;
				case '#':
					A[i][j] = -2;
					break;
				default:
					A[i][j] = INF;
			}
		}		
	}

	Elem S;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			if(A[i][j] == 0) {
				S.lin = i;
				S.col = j;
				BFS(S);
			}
		}
	}

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= N; j++) {
			if(A[i][j] == INF) {
				A[i][j] = -1;
			}
			cout << A[i][j] << " ";
		}
		cout << '\n';
	}



	return 0;
}
