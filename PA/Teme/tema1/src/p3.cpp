//
// CONSTANTIN MIHAI - 321CD
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

#define dmax 1005

int main() {

    FILE *in, *out;

    in = fopen("p3.in", "r");
    out = fopen("p3.out", "w");

    /**
    * d[i][j] = scorul maxim pe care il poate obtine Tuzgu din intervalul [i, j]
    */
    long d[dmax][dmax];
    vector<long> v;

    int N, i, j;
    long x, s = 0;

    fscanf(in, "%d", &N);

    v.push_back(-1); // indexare de la 1
    for (i = 0; i < N; i++) {
        fscanf(in, "%ld", &x);
        s += x;
        v.push_back(x);
    }

    /**
     * Cazul de baza 1
     *  d[i][i] = v[i]
     */

    for (i = 1; i <= N; i++) {
        d[i][i] = v[i];
    }

    /**
     * Cazul de baza 2:
     *  d[i][i + 1] = max(v[i], v[i + 1])
     */

    for (i = 1; i <= N; i++) {
        d[i][i + 1] = max(v[i], v[i + 1]);
    }

    /**
     * DP - recursive formula
     * d[i][j] = max(v[i] + min(d[i + 1][j - 1], d[i + 2][j]),
     *               v[j] + min(d[i][j - 2], d[i + 1][j - 1]))
     */

    for (int len = 2; len <= N; len++) {
        for (i = 1; i + len - 1 <= N; i++) {
            j = i + len - 1;

            d[i][j] = max(v[i] + min(d[i + 1][j - 1], d[i + 2][j]),
                          v[j] + min(d[i][j - 2], d[i + 1][j - 1]));
        }
    }

    long score_Tuzgu = d[1][N];
    long score_Ritza = s - score_Tuzgu;

    fprintf(out, "%ld\n", score_Tuzgu - score_Ritza);

    return 0;
}