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

	vector<int> visited;
	vector<int> parent;
	vector<int> idx;
	vector<int> lowlink;
	vector<int> ap;
	int indecs;

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

	void tarjan(int x) {

		int i, y, children;

		children = 0;
		idx[x] = lowlink[x] = indecs++;
		visited[x] = 1;

		// parcurg vecinii y ai lui x
		for(i = 0; i < adj[x].size(); i++) {
			y = adj[x][i];

			if(!visited[y]) {
				children++;
				parent[y] = x;
				tarjan(y);

				lowlink[x] = min(lowlink[x], lowlink[y]);

				if(parent[x] == -1 && children > 1) {
					ap[x] = 1;
				}

				if(parent[x] != -1 && lowlink[y] >= idx[x]) {
					ap[x] = 1;
				}
			}
			else {
				if(parent[x] != y) {
					lowlink[x] = min(lowlink[x], idx[y]); 
				}
			}
		}

	}

	vector<int> get_result() {
		/*
		TODO: Gasiti nodurile critice ale grafului neorientat stocat cu liste
		de adiacenta in adj.
		*/
		vector<int> sol;

		idx.resize(n + 1);
		lowlink.resize(n + 1);

		ap.resize(n + 1);
		ap.assign(n + 1, 0);

		parent.resize(n + 1);
		parent.assign(n + 1, -1);
		
		visited.resize(n + 1);
		visited.assign(n + 1, 0);

		// for(int i = 0; i <= n; i++) {
		// 	if(!visited[i]) {
		// 		tarjan(i);
		// 	}
		// }

		tarjan(0);

		for(int i = 0; i <= n; i++) {
			if(ap[i]) {
				printf("%d ", i);
			}
 		}
 		printf("\n");



		for(int i = 0; i <= n; i++) {
			if(ap[i]) {
				sol.push_back(i);
			}
		}

		return sol;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
