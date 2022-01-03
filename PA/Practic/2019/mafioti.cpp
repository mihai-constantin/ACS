#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define dmax 50005

vector<int> graph[dmax];
vector<int> transpus[dmax];
int N, M, Q;

bool visited[dmax];
bool visited_transpus[dmax];

void dfs(int x) {

	int y;

	visited[x] = true;

	// parcurg vecinii y ai lui x
	for(int i = 0; i < graph[x].size(); i++) {
		y = graph[x][i];

		if(!visited[y]) {
			dfs(y);
		}
	}
}

void dfs_transpus(int x) {

	int y;

	visited_transpus[x] = true;

	// parcurg vecinii y ai lui x
	for(int i = 0; i < transpus[x].size(); i++) {
		y = transpus[x][i];

		if(!visited_transpus[y]) {
			dfs_transpus(y);
		}
	}
}

// void write() {
// 	int i;
// 	printf("-----------------\n");
// 	for(i = 1; i <= N; i++) {
// 		printf("%d ", visited[i]);
// 	}
// 	printf("\n");
// 	for(i = 1; i <= N; i++) {
// 		printf("%d ", visited_transpus[i]);
// 	}
// 	printf("\n");
// }

void solve() {

	int i, j, x, y;
	bool gata = true;

	// citire graph
	for(i = 1; i <= M; i++) {
		scanf("%d %d", &x, &y);
		graph[x].push_back(y);
		transpus[y].push_back(x);
	}
	
	for(i = 1; i <= N; i++) {
		
		// initializare vector de vizitati
		memset(visited, 0, sizeof(visited));
		memset(visited_transpus, 0, sizeof(visited_transpus));

		dfs(i);
		dfs_transpus(i);

		// write();

		for(j = i + 1; j <= N; j++) {
			if(visited[j] == false && visited_transpus[j] == false) {
				gata = false;
				break;
			}
		}

		if(gata == false) {
			break;
		}
	}

	if(gata == true) {
		printf("1\n");
	}
	else {
		printf("0\n");
	}

	// INITIALIZARE GRAPH
	for(x = 1; x <= N; x++) {
		graph[x].clear();
		transpus[x].clear();
	}	
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

	int i;

	scanf("%d %d %d", &N, &M, &Q);
	for(i = 1; i <= Q; i++) {
		solve();
	}

    return 0;
}