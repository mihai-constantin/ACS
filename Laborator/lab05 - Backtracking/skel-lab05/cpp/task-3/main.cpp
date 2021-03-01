#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	bool GATA = false;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	void bkt(int p, vector<int> &sol, vector<int> &ans) {

		if(p == n + 1) {
			GATA = true;
	
			for(int k = 1; k <= n; k++) {
				ans[k] = sol[k];
			}

			return;	
		}

		for(int i = 1; i <= n && !GATA; i++) {

			bool ok = true;
			for(int j = 1; j < p; j++) {
				if(sol[j] == i || abs(p - j) == abs(sol[j] - i))
					ok = false;
			}

			if(ok == true) {
				sol[p] = i;
				bkt(p + 1, sol, ans);
				if(GATA){
					break;
				}
			}
		}
		
	}

	vector<int> get_result() {
		vector<int> sol(n + 1, 0);

		/*
		TODO: Gasiti o solutie pentru problema damelor pe o tabla de dimensiune
		n x n.

		Pentru a plasa o dama pe randul i, coloana j:
			sol[i] = j.
		Randurile si coloanele se indexeaza de la 1 la n.

		De exemplu, configuratia (n = 5)
		X----
		--X--
		----X
		-X---
		---X-
		se va reprezenta prin sol[1..5] = {1, 3, 5, 2, 4}.
		*/

		vector<int> ans(n + 1, 0);
		bkt(1, sol, ans);
		
		printf("-------------------\n");
		for(int k = 1; k <= n; k++) {
				printf("%d ", ans[k]);
			}
		printf("\n");
		
		return ans;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i != n ? ' ' : '\n');
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
