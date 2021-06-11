#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
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

	queue <int> q;
	vector <int> inQueue;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			adj[x].push_back(make_pair(y, w));
		}
		fin.close();
	}

	vector<int> get_result() {
		/*
		TODO: Gasiti distantele minime de la nodul source la celelalte noduri
		folosind BellmanFord pe graful orientat cu n noduri, m arce stocat in adj.
			d[node] = costul minim / lungimea minima a unui drum de la source la nodul
		node;
			d[source] = 0;
			d[node] = -1, daca nu se poate ajunge de la source la node.

		Atentie:
		O muchie este tinuta ca o pereche (nod adiacent, cost muchie):
			adj[x][i].first = nodul adiacent lui x,
			adj[x][i].second = costul.

		In cazul in care exista ciclu de cost negativ, returnati un vector gol:
			return vector<int>();
		*/

		int i, x, y, cost;
		vector<int> d(n + 1, INF);
		vector <int> visited(n + 1, 0);
		vector <int> pred(n + 1, -1);
		inQueue.resize(n + 1);

		// introduc in coada nodul de start
		q.push(source);
		inQueue[source] = 1;
		d[source] = 0;
		visited[source] = 1;

		while(!q.empty()) {
			x = q.front();
			q.pop();
			inQueue[x] = 0;

			// parcurg vecinii y ai lui x
			for(i = 0; i < adj[x].size(); i++) {
				y = adj[x][i].first;
				cost = adj[x][i].second;
				if(d[y] > d[x] + cost) {
					d[y] = d[x] + cost;
					pred[y] = x;

					if(!inQueue[y]) {
						q.push(y);
						inQueue[y] = 1;
						visited[y]++;
					}

					// am facut update la un nod de n ori -> "Ciclu negativ!"
					if(visited[y] == n) {
						d.clear();
						return d;
					}
				}
			}
		}

		for(i = 1; i <= n; i++) {
			if(d[i] == INF) {
				d[i] = -1;
			}
		}

		for(i = 1; i <= n; i++) {
			printf("%d ", pred[i]);
		}

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		if (result.size() == 0) {
			fout << "Ciclu negativ!\n";
		} else {
			for (int i = 1; i <= n; i++) {
				fout << result[i] << ' ';
			}
			fout << '\n';
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
