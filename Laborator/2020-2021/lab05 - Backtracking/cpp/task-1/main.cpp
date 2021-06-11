#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    int n, k;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin.close();
    }

    void bkt(int step, int stop, vector<int> &domain, vector<int> &solution, unordered_set<int> &visited, vector<vector<int> > &all) {
        if (step == stop) {
            all.push_back(solution);
            return;
        }

        for (int i = 0; i < domain.size(); i++) {
            if (visited.find(domain[i]) == visited.end()) {
                visited.insert(domain[i]);
                solution[step] = domain[i];
                bkt(step + 1, stop, domain, solution, visited, all);
                visited.erase(domain[i]);
            }
        }
    }

    vector<vector<int> > get_result() {
        vector<vector<int> > all;

        // TODO: Construiti toate aranjamentele de N luate cate K ale
        // multimii {1, ..., N}.
        //
        // Pentru a adauga un nou aranjament:
        //     vector<int> aranjament;
        //     all.push_back(aranjament);

        unordered_set<int> visited;
        vector<int> solution(k);
        vector<int> domain(n);
        for (int i = 0; i < n; i++) {
            domain[i] = i + 1;
        }

        bkt(0, k, domain, solution, visited, all);
        return all;
    }

    void print_output(const vector<vector<int> >& result) {
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
