#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define dmax 100005
#define INF 2000000005

vector<int> graph[dmax];
queue <int> q;

int d[dmax];

int N, M, S;

FILE *in, *out;

int main() {

	in = fopen("bfs.in", "r");
	out = fopen("bfs.out", "w");

	int i, x, y;

	fscanf(in, "%d %d %d", &N, &M, &S);
	for(i = 1; i <= M; i++) {
		fscanf(in, "%d %d", &x, &y);
		// muchia x -> y
		graph[x].push_back(y);
	}

	for(int i = 1; i <= N; i++) {
		d[i] = INF;
	}

	// adaug in coada nodul de start
	q.push(S);
	d[S] = 0;

	while(!q.empty()) {
		x = q.front();
		q.pop();

		// parcurg vecinii y ai lui x
		for(int i = 0; i < graph[x].size(); i++) {
			y = graph[x][i];

			if(d[y] > d[x] + 1) {
				d[y] = d[x] + 1;
				q.push(y);
			}
		}
	}

	for(int i = 1; i <= N; i++) {
		if(d[i] == INF){
			d[i] = -1;
		}
	}

	for(int i = 1; i <= N; i++) {
		fprintf(out, "%d ", d[i]);
	}
	fprintf(out, "\n");


	return 0;
}