#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;
	string caractere;
	vector<int> freq;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin >> caractere;
		caractere = " " + caractere; // Adaugare element fictiv -
									 // indexare de la 1.
		freq.push_back(-1); // Adaugare element fictiv - indexare de la 1.
		for (int i = 1, f; i <= n; i++) {
			fin >> f;
			freq.push_back(f);
		}
		fin.close();
	}

	void update(int stop, vector<char> &sir, vector<vector<char> > &all) {
		vector<char> sol(stop);
		for(int i = 1; i <= stop; i++) {
			sol[i - 1] = caractere.at(sir[i]);
		}
		all.push_back(sol);
	}

	bool valid(int p, vector<char> &sir, int x) {
		int nr = 0;
		for(int i = p - 1; i >= 0; i--) {
			if(sir[i] == x) {
				nr++;
			}
			else {
				break;
			}
		}

		if(nr >= k) {
			return false;
		}
		return true;
	}

	void bkt(int p, int stop, vector<char> &sir, vector<vector<char> > &all) {

		if(p == stop + 1) {
			update(stop, sir, all);
			return;
		}
		
		for(int i = 1; i <= n; i++) {
			if(freq[i] > 0 && valid(p, sir, i)) {
				freq[i]--;
				sir[p] = i;
				bkt(p + 1, stop, sir, all);
				freq[i]++;
			}
		}
	}

	vector<vector<char> > get_result() {
		vector<vector<char> > all;

		/*
		TODO: Construiti toate sirurile cu caracterele in stringul caractere
		(indexat de la 1 la n), si frecventele in vectorul freq (indexat de la
		1 la n), stiind ca nu pot fi mai mult de K aparitii consecutive ale
		aceluiasi caracter.

		Pentru a adauga un nou sir:
			vector<char> sir;
			all.push_back(sir);
		*/

		int total_freq = 0;
		for(int i = 1; i < freq.size(); i++) {
			total_freq += freq[i];
		}

		vector<char> sir(total_freq);
		bkt(1, total_freq, sir, all);

		return all;
	}

	void print_output(vector<vector<char> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j];
			}
			fout << '\n';
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
