#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream in("in");

#define dmax 25005

vector<pair<int, int> > edges;
int N, M, P;

int v[dmax];
int ord[dmax];

void solve() {

	int i;
	for(i = 1; i <= N; i++) {
		in >> v[i];
		ord[v[i]] = i;
	}

	bool ok = true;
	for(i = 0; i < edges.size(); i++) {
		if(ord[edges[i].first] > ord[edges[i].second]) {
			ok = false;
			break;
		}
	}

	if(ok) {
		cout << "DA\n";
	}
	else {
		cout << "NU\n";
	}

}

int main() {
	/* Cititi de la STDIN si afisati la STDOUT. Decomentati linia de mai jos daca
     * folositi cin/cout. Nu imbinati cin/cout cu scanf/printf in acest caz.
     */
	// ios::sync_with_stdio(false);

	int i, x, y;

	in >> N >> M >> P;
	for(i = 1; i <= M; i++) {
		in >> x >> y;
		edges.push_back(make_pair(x, y));
	}

	for(i = 1; i <= P; i++) {
		solve();
	}

    return 0;
}