#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <set>
#include <tuple>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<tuple<int, int, int> > edges;
	vector<int> parent, size;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y, w; i <= m; i++) {
			fin >> x >> y >> w;
			edges.push_back(make_tuple(w, x, y));
		}
		parent.resize(n + 1);
		size.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			parent[i] = i;
			size[i] = 1;
		}
		fin.close();
	}

	int find_root(int node) {
		if (node == parent[node]) {
			return node;
		}
		return parent[node] = find_root(parent[node]);
	}

	void merge_forests(int root1, int root2) {
		if (size[root1] <= size[root2]) {
			size[root2] += size[root1];
			parent[root1] = root2;
		} else {
			size[root1] += size[root2];
			parent[root2] = root1;
		}
	}

	int get_result() {
		/*
		TODO: Calculati costul minim al unui arbore de acoperire
		folosind algoritmul lui Kruskal.

		Pentru a construi un tuple:
		int a, b, c;
		tuple<int, int, int> t = make_tuple(a, b, c);

		Pentru a accesa elementele dintr-un tuple, exista 2 variante:
		tuple<int, int, int> t;
		int a, b, c;
		tie(a, b, c) = t;

		tuple<int, int, int> t;
		int a = get<0>(t);
		int b = get<1>(t);
		int c = get<2>(t);
		*/ 

		int result = 0;
		sort(edges.begin(), edges.end()); 

		int i, root1, root2;
		for(i = 0; i < edges.size(); i++) {
			root1 = find_root(get<1>(edges[i]));
			root2 = find_root(get<2>(edges[i]));

			if(root1 != root2) {
				merge_forests(root1, root2);
				result += get<0>(edges[i]);
			}
		}

		return result;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}
