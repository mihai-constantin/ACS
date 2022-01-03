#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <unordered_set>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}

	void bkt(int p, vector<vector<int> > &all, vector<int> &aranjament, unordered_set<int> &visited) {
		if(p == k) {
			all.push_back(aranjament);
			return;
		}

		for(int i = 1; i <= n; i++) {
			if(visited.find(i) == visited.end()){
				visited.insert(i);
				aranjament[p] = i;
				bkt(p + 1, all, aranjament, visited);
				visited.erase(i);
			}
			
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate aranjamentele de N luate cate K ale
		multimii {1, ..., N}.

		Pentru a adauga un nou aranjament:
			vector<int> aranjament;
			all.push_back(aranjament);
		*/

		vector<int> aranjament(k);
		unordered_set<int> visited(n);
		bkt(0, all, aranjament, visited);

		return all;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
