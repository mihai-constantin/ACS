#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

#define dmax 50005

vector<int> graph[dmax];
bool visited[dmax];
vector<int> sol;
int N, M;

FILE *in, *out;

void dfs(int x) {

	int i, y;

	visited[x] = true;

	// parcurg vecinii y ai lui x
	for(i = 0; i < graph[x].size(); i++) {
		y = graph[x][i];
		if(!visited[y]) {
			dfs(y);
		}
	}

	sol.push_back(x);
}

int main() {

	in = fopen("sortaret.in", "r");
	out = fopen("sortaret.out", "w");

	int i, x, y;

	fscanf(in, "%d %d", &N, &M);
	for(i = 1; i <= M; i++) {
		fscanf(in, "%d %d", &x, &y);
		graph[x].push_back(y);
	}

	for(i = 1; i <= N; i++) {
		if(!visited[i]) {
			dfs(i);
		}
	}

	for(i = sol.size() - 1; i >= 0; i--) {
		fprintf(out, "%d ", sol[i]);
	}
	fprintf(out, "\n");

	return 0;
}