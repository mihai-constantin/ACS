#include <iostream>
#include <fstream>
#include <cstdio>
#include <queue>

using namespace std;

#define dmax 1005
#define Dmax 5005
#define INF 2000000005

const int dlin[4] = {-1, 0, 1, 0};
const int dcol[4] = {0, 1, 0, -1};

typedef struct Elem {
	int lin;
	int col;
} Elem;

ifstream in("in");

int A[dmax][dmax];
int N, M, D;

int d1[dmax][dmax];
queue <Elem> q;

int gigel[Dmax];
int ionel[Dmax];

void Lee(Elem S) {

	Elem x, y;
	int k;

	d1[S.lin][S.col] = 0;
	q.push(S);

	while(!q.empty()) {
		x = q.front();
		q.pop();

		// parcurg vecinii y ai lui x
		for(k = 0; k < 4; k++) {
			y.lin = x.lin + dlin[k];
			y.col = x.col + dcol[k];

			if(y.lin >= 1 && y.lin <= N && y.col >= 1 && y.col <= M 
					&& d1[y.lin][y.col] > 1 + d1[x.lin][x.col]) {

				d1[y.lin][y.col] = 1 + d1[x.lin][x.col];
				q.push(y);
			}
		}
	}
}

int findMaxIonel(int st, int dr) {
	int maxim = ionel[st];

	for(int i = st + 1; i <= dr; i++) {
		if(maxim < ionel[i]) {
			maxim = ionel[i];
		}
	}
	return maxim;
}

int findMaxGigel(int st, int dr) {
	int maxim = gigel[st];

	for(int i = st + 1; i <= dr; i++) {
		if(maxim < gigel[i]) {
			maxim = gigel[i];
		}
	}
	return maxim;
}

int main()
{
	int i, j, x1, y1, x2, y2;
	Elem S;

	in >> N >> M >> D;
	in >> x1 >> y1;
	in >> x2 >> y2;
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			in >> A[i][j];
		}
	}

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			d1[i][j] = INF;
		}
	}

	S.lin = x1;
	S.col = y1;
	Lee(S);

	for(i = 0; i <= D; i++) {
		gigel[i] = -INF;
		ionel[i] = -INF;
	}

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			if(d1[i][j] <= D) {
				gigel[d1[i][j]] = max(gigel[d1[i][j]], A[i][j]);
			}
		}
	}

	// cout << "------------------------\n";
	// for(i = 0; i <= D; i++) {
	// 	cout << gigel[i] << " ";
	// }
	// cout << '\n';

	// PENTRU IONEL
	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			d1[i][j] = INF;
		}
	}

	S.lin = x2;
	S.col = y2;
	Lee(S);

	for(i = 1; i <= N; i++) {
		for(j = 1; j <= M; j++) {
			if(d1[i][j] <= D) {
				ionel[d1[i][j]] = max(ionel[d1[i][j]], A[i][j]);
			}
		}
	}

	// printf("*******************\n");
	// for(i = 1; i <= N; i++) {
	// 	for(j = 1; j <= M; j++) {
	// 		cout << d1[i][j] << " ";
	// 	}
	// 	cout << '\n';
	// }

	// cout << "------------------------\n";
	// for(i = 0; i <= D; i++) {
	// 	cout << ionel[i] << " ";
	// }
	// cout << '\n';

	int answer = -INF;
	int sol;

	// cautare solutie
	for(i = 0; i <= D; i++) {
		// gigel face i pasi
		// caut maximul in intervalul [0, D-i] in ionel
		sol = gigel[i] + findMaxIonel(0, D - i);
		if(sol > answer) {
			answer = sol;
		}
	}

	for(i = 0; i <= D; i++) {
		// ionel face i pasi
		// caut maximul in intervalul [0, D - i] in gigel
		sol = ionel[i] + findMaxGigel(0, D - i);
		if(sol > answer) {
			answer = sol;
		}

	}
	
	cout << answer << '\n';

	return 0;
}