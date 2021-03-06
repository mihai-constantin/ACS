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
    string expr;

    void read_input() {
        ifstream fin("in");
        fin >> n >> expr;
        expr = " " + expr; // adaugare caracter fictiv - indexare de la 1
        fin.close();
    }

    int get_result() {
        /*
        Calculati numarul de parantezari ale expresiei date astfel incat
        rezultatul sa dea true si returnati restul impartirii numarului
        la 10^9 + 7.
        */

        int length = expr.size();

        // T[i][j] = numarul de posibilitati de a paranteza de la i la j ai expresia sa fie evaluata la true
        vector<vector<int> > T(length, vector<int>(length, 0));

        // F[i][j] = numarul de posibilitati de a paranteza de la i la j ai expresia sa fie evaluata la false
        vector<vector<int> > F(length, vector<int>(length, 0));

        // cazul de baza - lungime expresie 1
        for (int i = 1; i < length; i++) {
            if (expr.at(i) == 'T') {
                T[i][i] = 1;
            } else if (expr.at(i) == 'F') {
                F[i][i] = 1;
            }
        }

        // recurenta - DP
        for (int len = 2; len < length; len++) {
            for (int i = 1; i + len - 1 < length; i++) {
                int j = i + len - 1;
                for (int k = i; k < j; k++) {
                    if (expr.at(k) == '|') {
                        T[i][j] =   (T[i][j] % kMod + 
                                    (1LL * (T[i][k - 1] % kMod) * (T[k + 1][j] % kMod)) % kMod +
                                    (1LL * (F[i][k - 1] % kMod) * (T[k + 1][j] % kMod)) % kMod +
                                    (1LL * (T[i][k - 1] % kMod) * (F[k + 1][j] % kMod)) % kMod) % kMod;
                        F[i][j] =   (F[i][j] % kMod + 
                                    (1LL * (F[i][k - 1] % kMod) * (F[k + 1][j] % kMod)) % kMod) % kMod;
                    } else if (expr.at(k) == '&') {
                        T[i][j] =   (T[i][j] % kMod + 
                                    (1LL * (T[i][k - 1] % kMod) * (T[k + 1][j] % kMod)) % kMod) % kMod;
                        F[i][j] =   (F[i][j] % kMod + 
                                    (1LL * (F[i][k - 1] % kMod) * (F[k + 1][j] % kMod)) % kMod +
                                    (1LL * (F[i][k - 1] % kMod) * (T[k + 1][j] % kMod)) % kMod +
                                    (1LL * (T[i][k - 1] % kMod) * (F[k + 1][j] % kMod)) % kMod) % kMod;
                    } else if (expr.at(k) == '^') {
                        T[i][j] =   (T[i][j] % kMod + 
                                    (1LL * (T[i][k - 1] % kMod) * (F[k + 1][j] % kMod)) % kMod +
                                    (1LL * (F[i][k - 1] % kMod) * (T[k + 1][j] % kMod)) % kMod) % kMod;
                        F[i][j] =   (F[i][j] % kMod + 
                                    (1LL * (F[i][k - 1] % kMod) * (F[k + 1][j] % kMod)) % kMod +
                                    (1LL * (T[i][k - 1] % kMod) * (T[k + 1][j] % kMod)) % kMod) % kMod;
                    }
                }
            }
        }

        cout << "=====  T   =====\n";
        for (int i = 1; i < length; i++) {
            for (int j = 1; j < length; j++) {
                cout << T[i][j] << " ";
            }
            cout << '\n';
        }

        cout << "=====  F   =====\n";
        for (int i = 1; i < length; i++) {
            for (int j = 1; j < length; j++) {
                cout << T[i][j] << " ";
            }
            cout << '\n';
        }

        return T[1][length - 1];
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
