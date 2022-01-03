#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <climits>
using namespace std;

const int kNmax = 1005;
const int INF = INT_MAX;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];
  	int C[kNmax][kNmax];
  	int F[kNmax][kNmax];
  	bool visited[kNmax];
  	int parent[kNmax];
  	vector <int> cd;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		memset(C, 0, sizeof C);
		for (int i = 1, x, y, z; i <= m; i++) {
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
     		C[x][y] += z;
		}
		fin.close();
	}

	int BF() {

		int k, i, x, y;

		memset(visited, 0, sizeof(visited));
		visited[1] = 1;

		cd.push_back(1);
		cd.push_back(1);

		for(k = 1; k < cd.size(); k++) {
			x = cd[k];

			for(i = 0; i < adj[x].size(); i++) {
				y = adj[x][i];

				if(C[x][y] != F[x][y] && !visited[y]) {
					visited[y] = true;
					parent[y] = x;
					cd.push_back(y);
					if(y == n) {
						return 1;
					}
				}
			}
		}

		return 0;
	}

	int get_result() {
		/*
		TODO: Calculati fluxul maxim pe graful orientat dat.
		Sursa este nodul 1.
		Destinatia este nodul n.

		In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
		arcelor, iar in C sunt stocate capacitatile arcelor.
		De exemplu, un arc (x, y) de capacitate z va fi tinut astfel:
		C[x][y] = z, adj[x] contine y, adj[y] contine x.
		*/

		int i, j, node, fmin, flow = 0;

		for(i = 1; i <= n; i++) {
			for(j = 1; j <= n; j++) {
				F[i][j] = 0;
			}
		}

		while(BF()) {
			fmin = INF;

			node = n;
			while(node != 1) {
				fmin = min(fmin, C[ parent[node] ][node] - F[ parent[node] ][node]);
				node = parent[node];
			}

			node = n;
			while(node != 1) {
				F[ parent[node] ][node] += fmin;
				F[node][ parent[node] ] -= fmin;
				node = parent[node];
			}

			flow += fmin;
			cd.clear();

		}

		return flow;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
