#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

ifstream in("in");

#define dmax 100005

long long v[dmax];
long long N;

int main() {
	/* Cititi de la STDIN si afisati la STDOUT. Decomentati linia de mai jos daca
     * folositi cin/cout. Nu imbinati cin/cout cu scanf/printf in acest caz.
     */
	// ios::sync_with_stdio(false);


	long long i, nr = 0, s = 0, minim, maxim;

	in >> N;
	for(i = 1; i <= N; i++) {
		in >> v[i];
		s += v[i];
		if(v[i] < 0) {
			nr++;
		}
	}

	if(nr == 0) {
		// am numai numere pozitive in vectorul v

		// calculez minimul din v
		minim = v[1];

		for(i = 2; i <= N; i++) {
			if(minim > v[i]) {
				minim = v[i];
			}
		}

		cout << s - 2 * minim << '\n';
	}
	else {
		if(nr == N) {

			// am numai numere negative
			maxim = v[1];
			for(i = 2; i <= N; i++) {
				if(maxim < v[i]) {
					maxim = v[i];
				}
			}

			cout << fabs(s) + 2 * maxim << '\n';
		}
		else {
			s = 0;
			for(i = 1; i <= N; i++) {
				if(v[i] > 0) {
					s += v[i];
				}
				else {
					s -= v[i];
				}
			}

			cout << s << '\n';
		}
		
	}


    return 0;
}