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
    int n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    void bkt(int p, vector<vector<int> > &all, vector<int> &submultime) {
        vector<int> sol(submultime.begin() + 1, submultime.begin() + p);
        all.push_back(sol);

        for(int i = submultime[p - 1] + 1; i <= n; i++) {
            submultime[p] = i; 
            bkt(p + 1, all, submultime);
        }
    }

    vector<vector<int> > get_result() {
        vector<vector<int> > all;

        // TODO: Construiti toate submultimile multimii {1, ..., N}.
        //
        // Pentru a adauga o noua submultime:
        //     vector<int> submultime;
        //     all.push_back(submultime);

        vector<int> submultime(n);
        bkt(1, all, submultime);
	    return all;
    }

    void print_output(const vector<vector<int>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                fout << result[i][j] << (j + 1 != result[i].size() ? ' ' : '\n');
            }
        }
        fout.close();
    }
};

// [ATENTIE] NU modifica functia main!
int main() {
    // * se aloca un obiect Task pe heap
    // (se presupune ca e prea mare pentru a fi alocat pe stiva)
    // * se apeleaza metoda solve()
    // (citire, rezolvare, printare)
    // * se distruge obiectul si se elibereaza memoria
    auto* task = new (std::nothrow) Task{}; // hint: cppreference/nothrow
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
