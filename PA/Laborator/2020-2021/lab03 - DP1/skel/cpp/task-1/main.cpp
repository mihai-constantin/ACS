#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, S;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n >> S;
        v.push_back(-1); // adaugare element fictiv - indexare de la 1
        for (int i = 1, e; i <= n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati numarul minim de monede ce poate fi folosit pentru a obtine
        suma S. Tipurile monedelor sunt stocate in vectorul v, de dimensiune n.
        */
        vector<int> scores;
        scores.resize(S + 1, -1);
        scores[0] = 0;
        for (int i = 1; i <= n; i++) {
            cout << v[i] << '\n';
            for (int j = v[i]; j <= S; j++) {
                if (scores[j] == -1 && scores[j - v[i]] != -1) {
                    scores[j] = 1 + scores[j - v[i]];
                } else if (scores[j] > 1 + scores[j - v[i]]) {
                    scores[j] = 1 + scores[j - v[i]];
                }
            }
            for (int j = 0; j <= S; j++) {
                cout << scores[j] << " ";
            }
            cout << '\n';
        }
       
        cout << "score: " << scores[S] << '\n';
        return scores[S];
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
