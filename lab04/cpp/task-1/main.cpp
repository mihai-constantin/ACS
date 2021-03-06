#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int kMod = 1e9 + 7;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        /*
        Calculati numarul de subsiruri ale lui v cu suma numerelor para si
        returnati restul impartirii numarului la 10^9 + 7.
        */

        vector<vector<int> > dp(n + 1, vector<int>(2,0)); // matrice de dimensiune (n + 1) x (2)

        /**
         * 
         * dp[i][1] = numarul de submultimi cu suma numerelor impara cu primele i numere din sir
         * dp[i][0] = numarul de submultimi cu suma numerelor para cu primele i numere din sir
         * 
         */
        
        dp[0][0] = 1; // multimea vida - suma 0
        dp[0][1] = 0;

        for (int i = 1; i <= n; i++) {
            if (v[i] % 2 == 0) {
                dp[i][0] = (2 * (dp[i - 1][0] % kMod)) % kMod;
                dp[i][1] = (2 * (dp[i - 1][1] % kMod)) % kMod;
            } else {
                dp[i][0] = ((dp[i - 1][0] % kMod) + (dp[i - 1][1] % kMod)) % kMod;
                dp[i][1] = ((dp[i - 1][0] % kMod) + (dp[i - 1][1] % kMod)) % kMod;
            }
        }

        return dp[n][0] - 1; // fara multimea vida
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
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
