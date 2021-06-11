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

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y); // graf orientat
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Faceti sortarea topologica a grafului stocat cu liste de
		adiacenta in adj.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		vector<int> topsort;
		vector<int> d(n + 1, 0);

		int x, y, i;
		for(x = 1; x <= n; x++) {
			// parcurg vecinii y ai lui x
			for(i = 0; i < adj[x].size(); i++) {
				y = adj[x][i];
				d[y]++;
			}
		}

		queue<int> q;
		
		// introduc in coada toate nodurile i cu d[i] = 0
		for(i = 1; i <= n; i++) {
			if(d[i] == 0) {
				q.push(i);
			}
		}

		while(!q.empty()) {
			x = q.front();
			topsort.push_back(x);
			q.pop();

			// parcurg vecinii nodului x
			for(i = 0; i < adj[x].size(); i++) {
				y = adj[x][i];
				d[y]--;

				if(d[y] == 0) {
					q.push(y);
				}
			}
		}

		return topsort;
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
