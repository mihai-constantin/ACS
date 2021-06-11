#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define dmax 6000002

ifstream in("in");
ofstream out("pwdout");

int N;
int v[dmax], bst[dmax];

int main(void) {

	int i, maxim, left, right, idx;

    in >> N;
	for(i = 1; i <= N; i++) {
        in >> v[i];
	}

	bst[1] = v[1];
	maxim = bst[1];
	left = right = 1;
	for(i = 2; i <= N; i++) {
		// bst[i] = max(bst[i - 1] + v[i], v[i]);

		if(bst[i - 1] < 0) {
			idx = i;
		}

		bst[i] = v[i];
		if(bst[i - 1] + v[i] > bst[i]) {
			bst[i] = bst[i - 1] + v[i];
		}

		if(maxim < bst[i]){
			maxim = bst[i];
			left = idx;
			right = i;
		}
	}

    out << maxim << " " << left << " " << right << '\n';

	return 0;
}
