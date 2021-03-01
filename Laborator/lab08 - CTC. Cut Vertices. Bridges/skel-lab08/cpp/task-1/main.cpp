#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
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
	vector<int> adjt[kNmax];

	vector<int> idx;
	vector<int> lowlink;
	vector<int> in_stack;
	stack <int> S;
	int indecs;

	vector<int> comp;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	void tarjan(vector< vector<int> > &sol, int x) {

		int i, y, node;

		idx[x] = lowlink[x] = indecs++;
		S.push(x);
		in_stack[x] = 1;

		// parcurg vecinii y ai lui x
		for(i = 0; i < adj[x].size(); i++) {
			y = adj[x][i];

			if(idx[y] == -1) {
				tarjan(sol, y);
				lowlink[x] = min(lowlink[x], lowlink[y]);
			}
			else {
				if(in_stack[y]) {
					lowlink[x] = min(lowlink[x], lowlink[y]);
				}
			}
		}

		if(idx[x] == lowlink[x]) {
			// este x radacina unei CTC ?
			comp.clear();
			do
			{
				node = S.top();
				// printf("%d ", node);
				comp.push_back(node);
				S.pop();
				in_stack[node] = 0;
			} while(x != node);

			// printf("\n");

			sol.push_back(comp);

		}
	}

	vector<vector<int>> get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.
		
		Atentie: graful transpus este stocat in adjt.
		*/
		vector<vector<int>> sol;

		idx.resize(n + 1);
		idx.assign(n + 1, -1);
		lowlink.resize(n + 1);
		in_stack.resize(n + 1);
		in_stack.assign(n + 1, 0);

		int i;
		for(i = 1; i <= n; i++) {
			if(idx[i] == -1) {
				tarjan(sol, i);
			}
		}


		return sol;
	}

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
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
