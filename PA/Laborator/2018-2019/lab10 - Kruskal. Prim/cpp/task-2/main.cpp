#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <tuple>
#include <queue>
using namespace std;

#define INF INT_MAX

const int kNmax = 2e5 + 10;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<pair<int, int> > adj[kNmax];
	priority_queue<pair <int, int>> H;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
			adj[y].push_back(make_pair(x, w));
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Calculati costul minim al unui arbore de acoperire
		folosind algoritmul lui Prim.
		*/

		int i, x, y, cost;

		vector<int> d(n + 1, INF);
		vector<int> visited(n + 1, 0);
		vector<int> parent(n + 1, -1);

		// introduc in heap nodul de start
		H.push(make_pair(0, 1));
		d[1] = 0;

		while(!H.empty()) {

			while(!H.empty() && visited[H.top().second]) {
				H.pop();
			}

			if(H.empty()) {
				break;
			}

			x = H.top().second;
			visited[x] = 1;

			// parcurg vecinii nodului x
			for(i = 0; i < adj[x].size(); i++) {
				y = adj[x][i].first;
				cost = adj[x][i].second;

				if(d[y] > cost && !visited[y]) {
					parent[y] = x;
					d[y] = cost;
					H.push(make_pair(-d[y], y));
				}
			}
		}

		int result = 0;
		for(i = 1; i <= n; i++) {
			printf("%d %d\n", parent[i], i);
			if(parent[i] != -1) {
				result += d[i];
			}

		}

		return result;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
