#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <climits>
using namespace std;

#define INF INT_MAX

const int kNmax = 50005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
	vector<pair<int, int> > adj[kNmax];
	priority_queue<pair <int, int> > H;
	vector<int> pred;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	void drum(int node) {
		if(node == 1) {
			printf("%d ", node);
			return;
		}

		drum(pred[node]);
		printf("-> %d ", node);
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind Dijkstra pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.
		*/
		int i, x, y, cost;
		vector<int> d(n + 1, INF);
		vector<int> visited(n + 1, 0);
		pred.resize(n + 1);
		pred.assign(n + 1, -1);
		// introduc in heap nodul de start
		H.push(make_pair(0, source));
		d[source] = 0;
		pred[source] = 0;

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

				if(d[y] > d[x] + cost) {
					d[y] = d[x] + cost;
					pred[y] = x;
					H.push(make_pair(-d[y], y));
				}
			}

		}

		for(i = 1; i <= n; i++) {
			if(d[i] == INF) {
				d[i] = -1;
			}
		}

		int dest;
		cout << "dest: ";
		cin >> dest;
		drum(dest);
		cout << '\n';

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
