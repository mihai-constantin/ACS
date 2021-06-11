#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, S;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n >> S;
		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result() {
		/*
		TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
		suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
		*/
		vector<int> d(S + 1, INT_MAX);
		d[0] = 0;
		for(int i = 0; i < v.size(); i++) {
			d[v[i]] = 1;
		}

		for(int i = 1; i <= n; i++) {
			for(int j = v[i]; j <= S; j++) {
				if(d[j] > d[j - v[i]] + 1 && d[j - v[i]] != INT_MAX) {
					d[j] = 1 + d[j - v[i]];
				}
			}
		}

		for(int i = 0; i < d.size(); i++) {
			printf("%d ", d[i]);
		}
		printf("\n");

		if(d[S] == INT_MAX) {
			return -1;
		}

		return d[S];
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
