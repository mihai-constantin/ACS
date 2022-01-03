#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;
const int INF = 2000000005;

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
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
		vector<int> d(n + 1);
		/*
		TODO: Faceti un BFS care sa construiasca in d valorile d[i] = numarul
		minim de muchii de parcurs de la nodul source la nodul i.
		d[source] = 0
		d[x] = -1 daca nu exista drum de la source la x.
		*******
		ATENTIE: nodurile sunt indexate de la 1 la n.
		*******
		*/
		
		// initializare vector de distante
		for(int i = 1; i <= n; i++) {
			d[i] = INF;
		}

		queue<int> q;

		// inserez in coada nodul de start 
		q.push(source);
		d[source] = 0;

		while(!q.empty()){
			int x = q.front();
			q.pop();

			// parcurg vecinii nodului x
			for(int i = 0; i < adj[x].size(); i++) {
				int y = adj[x][i];

				if(d[y] > d[x] + 1) {
					d[y] = d[x] + 1;
					q.push(y);
				}
			}
		}

		for(int i = 1; i <= n; i++) {
			if(d[i] == INF){
				d[i] = -1;
			}
		}

		return d;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
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
