#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Result {
	int len;
	vector<int> subsequence;
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> v;
	vector<int> w;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}

		w.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= m; i++) {
			fin >> e;
			w.push_back(e);
		}

		fin.close();
	}

	Result get_result() {
		Result result;
		result.len = 0;

		/*
		TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
		si w (de lungime m).
		Se puncteaza separat urmatoarele 2 cerinte:
		2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune in
		``result.len``.
		2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal valid.
		Solutia pentru aceasta cerinta se va pune in ``result.subsequence``.
		*/

		int i, j;

		vector<vector<int> > d(n + 1);
		for(i = 0; i <= n; i++) {
			d[i].reserve(m + 1);
			for(j = 0; j <= m; j++) {
				d[i].push_back(0);
			}
		}

		for(i = 1; i <= n; i++) {
			for(j = 1; j <= m; j++) {
				if(v[i] == w[j]) {
					d[i][j] = 1+ d[i - 1][j - 1];
				}
				else {
					d[i][j] = max(d[i - 1][j], d[i][j - 1]);
				}
			}
		}

		for(i = 1; i <= n; i++) {
			for(j = 1; j <= m; j++) {
				printf("%d ", d[i][j]);
			}
			printf("\n");
		}

		result.len = d[n][m];

		// reconstruire solutie CMLSM

		i = n;
		j = m;
		while(i != 0 && j != 0) {
			if(v[i] == w[j]) {
				result.subsequence.push_back(v[i]);
				i--;
				j--;
			}
			else {
				if(d[i - 1][j] > d[i][j - 1]) {
					i--;
				}
				else {
					j--;
				}
			}
		}

		std::reverse(std::begin(result.subsequence), std::end(result.subsequence)); 

		for(i = 0; i < result.subsequence.size(); i++) {
			printf("%d ", result.subsequence[i]);
		}
		printf("\n");

		return result;
	}

	void print_output(Result result) {
		ofstream fout("out");
		fout << result.len << '\n';
		for (int x : result.subsequence) {
			fout << x << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
