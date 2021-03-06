#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Result {
    int len;
    vector<int> subsequence;
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m;
    vector<int> v;
    vector<int> w;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;

        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }

        w.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= m; i++) {
            fin >> e;
            w.push_back(e);
        }

        fin.close();
    }

    Result get_result() {
        Result result;
        result.len = 0;

        /*
        TODO: Aflati cel mai lung subsir comun intre v (de lungime n)
        si w (de lungime m).
        Se puncteaza separat urmatoarele 2 cerinte:
        2.1. Lungimea CMLSC. Rezultatul pentru cerinta aceasta se va pune in
        ``result.len``.
        2.2. Reconstructia CMLSC. Se puncteaza orice subsir comun maximal valid.
        Solutia pentru aceasta cerinta se va pune in ``result.subsequence``.
        */

        int i, j;

        vector< vector<int> > dp(n + 1);
        for (i = 0; i <= n; ++i) {
            dp[i].resize(m + 1);
        }

        for (i = 1; i <= n; i++) {
            for (j = 1; j <= m; j++) {
                if (v[i] == w[j]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        for (i = 0; i <= n; i++) {
            for (j = 0; j <= m; j++) {
                cout << dp[i][j] << " ";
            }
            cout << '\n';
        }

        result.len = dp[n][m];
        result.subsequence.resize(result.len);

        i = n;
        j = m;
        int len = result.len - 1;
        while(i != 0 && j != 0) {
            if (v[i] == w[j]) {
                result.subsequence[len] = v[i];
                len--;
                i--;
                j--;
            } else {
                if (dp[i - 1][j] > dp[i][j - 1]) {
                    i--;
                } else {
                    j--;
                }
            }
        }

        cout << "len max: " << result.len << '\n';
        for (i = 0; i < result.len; i++) {
            cout << result.subsequence[i] << " ";
        }
        cout << '\n';

        return result;
    }

    void print_output(Result result) {
        ofstream fout("out");
        fout << result.len << '\n';
        for (int x : result.subsequence) {
            fout << x << ' ';
        }
        fout << '\n';
        fout.close();
    }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
