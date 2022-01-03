#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 105;

class Task {
 public:
	void solve() {
		read_input();
		compute();
		print_output();
	}

 private:
	int n;
	int d[kNmax][kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fin >> d[i][j];
			}
		}
		fin.close();
	}

	void compute() {
		/*
		TODO: Gasiti distantele minime intre oricare doua noduri, folosind RoyFloyd
		pe graful orientat cu n noduri, m arce stocat in matricea ponderilor a
		(declarata mai sus).

		Atentie:
		O muchie (x, y, w) este reprezentata astfel in matricea ponderilor:
			a[x][y] = w;
		Daca nu exista o muchie intre doua noduri x si y, in matricea ponderilor
		se va afla valoarea 0:
			a[x][y] = 0;

		Trebuie sa populati matricea d[][] (declarata mai sus):
			d[x][y] = distanta minima intre nodurile x si y, daca exista drum.
			d[x][y] = 0 daca nu exista drum intre x si y.
			d[x][x] = 0.
		*/

		int i, j, k;
		for(k = 1; k <= n; k++) {
			for(i = 1; i <= n; i++) {
				for(j = 1; j <= n; j++) {
					if(((d[i][j] > d[i][k] + d[k][j]) || !d[i][j]) && i != j && d[i][k] && d[k][j]) {
						d[i][j] = d[i][k] + d[k][j];
					}
				}
			}
		}

	}

	void print_output() {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				fout << d[i][j] << ' ';
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
