#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

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

	vector<int> idx;
	vector<int> lowlink;
	vector<int> visited;
	vector<int> parent;
	int indecs;

	struct Edge {
		int x;
		int y;
	};

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			// graf neorientat
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void dfs_critical_edge(vector<Edge> &sol, int x) {
		int i, y;
		Edge edge;
		idx[x] = lowlink[x] = indecs++;
		visited[x] = true;

		// parcurg vecinii y ai lui x
		for(i = 0; i < adj[x].size(); i++) {
			y = adj[x][i];

			if(!visited[y]) {

				parent[y] = x;
				dfs_critical_edge(sol, y);

				lowlink[x] = min(lowlink[x], lowlink[y]);

				if(lowlink[y] > idx[x]) {
					printf("x = %d y = %d\n", x, y);
					edge.x = x;
					edge.y = y;
					sol.push_back(edge);
				}

			}
			else {
				if(parent[x] != y) {
					lowlink[x] = min(lowlink[x], idx[y]);
				}
			}
		}

	}


	vector<Edge> get_result() {
		/*
		TODO: Gasiti muchiile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/

		int i;
		vector<Edge> sol;

		idx.resize(n + 1);
		lowlink.resize(n + 1);

		visited.resize(n + 1);
		visited.assign(n + 1, 0);

		parent.resize(n + 1);
		parent.assign(n + 1, -1);

		// for(i = 0; i <= n; i++) {
		// 	if(!visited[i]) {
		// 		dfs_critical_edge(sol, i);
		// 	}
		// }

		dfs_critical_edge(sol, 0);

		printf("idx: ");
		for(i = 0; i <= n; i++) {
			printf("%d ", idx[i]);
		}
		printf("\n");

		printf("lowlink: ");
		for(i = 0; i <= n; i++) {
			printf("%d ", lowlink[i]);
		}
		printf("\n");

		printf("visited: ");
		for(i = 0; i <= n; i++) {
			printf("%d ", visited[i]);
		}
		printf("\n");

		printf("parent: ");
		for(i = 0; i <= n; i++) {
			printf("%d ", parent[i]);
		}
		printf("\n");

		return sol;
	}

	void print_output(vector<Edge> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i].x << ' ' << result[i].y << '\n';
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
