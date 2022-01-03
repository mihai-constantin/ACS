#include <iostream>
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
	vector<int> adjt[kNmax];
	bool visited[kNmax];
	vector<int> topological_sort;
	vector<int> comp;


	void read_input() {
		ifstream fin("kosaraju.in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	void sortaret(int x) {

		int i, y;

		visited[x] = true;

		// parcurg vecinii y ai lui x
		for(i = 0; i < adj[x].size(); i++) {
			y = adj[x][i];

			if(!visited[y]) {
				sortaret(y);
			}
		}

		topological_sort.push_back(x);
	}

	void dfs(int x) {

		int i, y;

		visited[x] = true;
		comp.push_back(x);

		// parcurg vecinii nodului x
		for(i = 0; i < adjt[x].size(); i++) {
			y = adjt[x][i];
			if(!visited[y]) {
				dfs(y);
			}
		}

	}

	vector< vector<int> > get_result() {
		/*
		TODO: Gasiti componentele tare conexe ale grafului orientat cu
		n noduri, stocat in adj. Rezultatul se va returna sub forma
		unui vector, ale carui elemente sunt componentele tare conexe
		detectate. Nodurile si componentele tare conexe pot fi puse in orice
		ordine in vector.
		
		Atentie: graful transpus este stocat in adjt.
		*/

		int i;
		vector< vector<int> > sol;

		// Fac o sortare topologica pe graful normal.

		for(i = 1; i <= n; i++) {
			if(!visited[i]) {
				sortaret(i);
			}
		}

		for(i = topological_sort.size() - 1; i >= 0; i--) {
			printf("%d ", topological_sort[i]);
		}
		printf("\n");

		for(i = 1; i <= n; i++) {
			visited[i] = false;
		}

		for(i = topological_sort.size() - 1; i >= 0; i--) {
			if(!visited[topological_sort[i]]) {
				comp.clear();
				dfs(topological_sort[i]);
				sol.push_back(comp);
			}
		}


		return sol;
	}

	void print_output(vector< vector<int> > result) {
		ofstream fout("kosaraju.out");
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
