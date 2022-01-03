#include <cmath>
#include <cstdio>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

ifstream in("in");

#define dmax 100005
int v[dmax];
int N, K;

int main() {
    /*
     * Daca vreti sa folositi iostream(cin si cout) in loc de stdio(scanf si printf), decomentati linia urmatoare
     * cin este mult mai lent decat scanf in general, dar decomentand linia nu se va simti diferenta de timp
     * Nu folositi stdio daca decomentati linia => posibile probleme de sincronizare
     **/
    
    std::ios::sync_with_stdio(false);  
  
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int i, s = 0;

    in >> N >> K;
    for(i = 1; i <= N; i++) {
    	in >> v[i];
    }

    sort(v + 1, v + N + 1);

    for(i = 1; i <= N; i++) {
    	cout << v[i] << " ";
    }
    cout << '\n';
    cout << "---------------\n";

    for(i = 1; i <= N; i++) {
    	if(v[i] < 0 && K) {
    		v[i] = -v[i];
    		K--;
    	}
    	else {
    		break;
    	}
    }

    if(K > 0) {
    	if(K % 2 == 1) {
    		v[i] = -v[i];
    	}
    }

    for(i = 1; i <= N; i++) {
    	s += v[i];
    	cout << v[i] << " ";
    }
    cout << '\n';

    cout << s << "\n";
  
    return 0;
}