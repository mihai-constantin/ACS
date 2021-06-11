#include <iostream>
#include <fstream>
using namespace std;

#define dmax 100005

ifstream in("in");
ofstream out("out");

int v[dmax];
int N;

int bst[dmax], pred[dmax], sol[dmax];

int main(void) {

	in >> N;
	for(int i = 1; i <= N; i++) {
		in >> v[i];
	}


	bst[1] = 1;
	pred[1] = 0;

	for(int i = 2; i <= N; i++) {
		bst[i] = 1;
		pred[i] = 0;
	
		for(int j = 1; j < i; j++) {
			if(v[j] < v[i]) {
				if(1 + bst[j] > bst[i]) {
					bst[i] = 1 + bst[j];
					pred[i] = j;
				}
			}
		}
	}

	int maxLength = bst[1];
	int pos = 1;
	for(int i = 1; i <= N; i++) {
		if(maxLength < bst[i]) {
			maxLength = bst[i];
			pos = i;
		}
	}

	out << maxLength << "\n";

	for(int i = maxLength; i >= 1; i--) {
		sol[i] = v[pos];
		pos = pred[pos];
	}

	for(int i = 1; i <= maxLength; i++){
		out << sol[i] << " ";
	}
	out << "\n";

	return 0;
}
