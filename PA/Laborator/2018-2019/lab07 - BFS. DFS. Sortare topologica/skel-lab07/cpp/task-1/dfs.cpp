#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

#define dmax 100005

vector<int> graph[dmax];

bool visited[dmax];
int N, M;

int componente;

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
}

int main() {

	in = fopen("dfs.in", "r");
	out = fopen("dfs.out", "w");

	int i, x, y;

	fscanf(in, "%d %d", &N, &M);

	for(i = 1; i <= M; i++) {
		fscanf(in, "%d %d", &x, &y);
		graph[x].push_back(y);
	}

	// for(i = 1; i <= N; i++) {
	// 	if(!visited[i]){
	// 		dfs(i);
	// 		componente++;
	// 	}
	// }

	dfs(1);

	for(i = 1; i <= N; i++) {
		printf("%d ", visited[i]);
	}
	printf("\n");

	fprintf(out, "%d\n", componente);

	return 0;
}