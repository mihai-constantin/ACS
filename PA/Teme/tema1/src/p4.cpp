//
// CONSTANTIN MIHAI - 321CD
//

#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const unsigned long long int mod = 1000000007;

FILE *in, *out;

unsigned long long N, K, V;

unsigned long long int modulo(unsigned long long int x) {

    while (x >= mod) {
        unsigned long long q = x / mod;
        x -= q * mod;
    }

    return x;
}

vector<vector<unsigned long long>> create_matrix(unsigned long long n, unsigned long long m) {

    unsigned long long i, j;
    vector<vector<unsigned long long>> d(n + 2, vector<unsigned long long>(m + 2, 0));

    for (i = 1; i <= n; i++) {
        d[i][0] = 1;
    }

    for (j = 1; j <= m; j++) {
        d[1][j] = 1;
    }
    for (i = 2; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            d[i][j] = modulo(modulo(d[i][j - 1]) + modulo(d[i - 1][j]));

        }
    }

    return d;
}

int main() {

    in = fopen("p4.in", "r");
    out = fopen("p4.out", "w");

    unsigned long long i, n, m;
    fscanf(in, "%llu %llu %llu", &N, &K, &V);

    /**
     * Invalid cases
     */
    if (N / 2 > K || (long long) (V - K - N / 2) < 0) {
        fprintf(out, "0\n");
        return 0;
    }

    unsigned long long res1, res2;

    // N even
    if (N & 1) {
        // DP for differences between two adjacent numbers in a sorted array
        n = 1 + N / 2;
        m = K - n;

        vector<vector<unsigned long long >> dp1 = create_matrix(n, m);
        res1 = dp1[n][m];

    } else {
        // N odd

        // DP for differences between two adjacent numbers in a sorted array
        n = N / 2;
        m = K - n;
        vector<vector<unsigned long long >> dp1 = create_matrix(n, m);
        res1 = dp1[n][m];
    }

    // DP for gaps between differences

    n = N / 2;
    m = V - K - n;
    vector<vector<unsigned long long>> d2 = create_matrix(n, m);

    /**
     * res2 would be the sum of d2[n][i], i = 0 : V - K - N/2
     */
    unsigned long long limit = V - K - N / 2;
    res2 = 0;
    for (i = 0; i <= limit; i++) {
        res2 = modulo(modulo(res2) + modulo(d2[n][i]));
    }

    /**
     * Calculate factorial of N
     */
    unsigned long long factorial = 1;
    for (i = 2; i <= N; i++) {
        factorial = modulo(modulo(factorial) * modulo(i));
    }

    unsigned long long partial_res = modulo(modulo(res1) * modulo(res2));
    unsigned long long final_res = modulo(modulo(partial_res) * modulo(factorial));
    fprintf(out, "%llu\n", final_res);

    return 0;
}
