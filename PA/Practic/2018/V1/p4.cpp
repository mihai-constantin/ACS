#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define dmax 100005

ifstream in("in");
ofstream out("out");

vector<pair<int, int> > graph[dmax];
int N, M;

int gradInt[dmax];
int gradExt[dmax];

bool source[dmax];
bool dest[dmax];

int sol[dmax];
bool visited[dmax];

int minim;

vector <pair<int, pair<int, int> > > solution;

void calculate(int n) {
	
	if(minim == INT_MAX) {
		minim = 0;
	}

	solution.push_back(make_pair(sol[1], make_pair(sol[n], minim)));
}

void bkt(int p) {

	int x, y, cost;

	if(dest[sol[p - 1]] == true) {
		// am gasit un lant
		calculate(p - 1);
		return;
	}

	// parcurg vecinii lui sol[p - 1]
	x = sol[p - 1];
	for(int i = 0; i < graph[x].size(); i++) {
		y = graph[x][i].first;
		cost = graph[x][i].second;

		if(!visited[y]) {
			sol[p] = y;
			visited[y] = true;
			minim = min(minim, cost);
			bkt(p + 1);
			visited[y] = false;
		}
	}
}

int main()
{
	int i, x, y, c;

	in >> N >> M;
	for(i = 1; i <= M; i++) {
		in >> x >> y >> c;
		// graf orientat
		graph[x].push_back(make_pair(y, c));

		gradInt[y]++;
		gradExt[x]++;
	}

	for(i = 1; i <= N; i++) {
		if(gradInt[i] == 0) {
			// i e surs
			source[i] = true;
		}

		if(gradExt[i] == 0) {
			dest[i] = true;
		}
	}

	for(i = 1; i <= N; i++) {
		if(source[i]) {
			minim = INT_MAX;
			sol[1] = i;
			bkt(2);
		}
	}

	out << solution.size() << '\n';
	for(i = 0; i < solution.size(); i++) {
		out << solution[i].first << " " << solution[i].second.first << " " << solution[i].second.second << '\n';
	}

	return 0;
}