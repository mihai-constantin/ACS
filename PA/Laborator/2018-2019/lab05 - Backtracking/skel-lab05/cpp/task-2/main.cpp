#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	void bkt(int p, vector<vector<int> > &all, vector<int> &submultime) {
		
		vector<int> sol(submultime.begin() + 1, submultime.begin() + p);
		all.push_back(sol);

		for(int i = submultime[p - 1] + 1; i <= n; i++) {
				submultime[p] = i; 
				bkt(p + 1, all, submultime);
		}
	}

	vector<vector<int> > get_result() {
		vector<vector<int> > all;

		/*
		TODO: Construiti toate submultimile multimii {1, ..., N}.

		Pentru a adauga o noua submultime:
			vector<int> submultime;
			all.push_back(submultime);
		*/

		vector<int> submultime(n);
		bkt(1, all, submultime);

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
