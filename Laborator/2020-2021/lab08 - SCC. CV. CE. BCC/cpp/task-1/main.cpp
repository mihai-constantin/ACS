#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    vector<int> idx;
    vector<int> lowlink;
    vector<int> in_stack;
    stack<int> S;
    int indecs;

    vector<int> comp;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y;
            adj[x].push_back(y); // arc (x, y)
        }
        fin.close();
    }

    void tarjan(vector< vector<int> > &sol, int x) {
        int i, y, node;

        idx[x] = lowlink[x] = indecs++;
        S.push(x);
        in_stack[x] = 1;

        // parcurg vecinii y ai lui x
        for (i = 0; i < adj[x].size(); i++) {
            y = adj[x][i];

            if (idx[y] == -1) {
                tarjan(sol, y);
                lowlink[x] = min(lowlink[x], lowlink[y]);
            } else if (in_stack[y]) {
                lowlink[x] = min(lowlink[x], lowlink[y]);
            }
        }

        // x radacina pentru CTC
        if (idx[x] == lowlink[x]) {
            comp.clear();
            do {
                node = S.top();
                comp.push_back(node);
                S.pop();
                in_stack[node] = 0;
            } while(node != x);

            sol.push_back(comp);
        }
    }

    vector<vector<int>> get_result() {
        //
        // TODO: Găsiți componentele tare conexe  (CTC / SCC) ale grafului orientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un SCC (adică tot un vector).
        // * nodurile dintr-un SCC pot fi găsite în orice ordine
        // * SCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru SCC.
        //

        vector<vector<int>> all_sccs;

        idx.resize(n + 1);
        idx.assign(n + 1, -1);
        
        lowlink.resize(n + 1);

        in_stack.resize(n + 1);
        in_stack.assign(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            if (idx[i] == -1) {
                tarjan(all_sccs, i);
            }
        }

        return all_sccs;
    }

    void print_output(const vector<vector<int>>& all_sccs) {
        ofstream fout("out");
        fout << all_sccs.size() << '\n';
        for (const auto& scc : all_sccs) {
            for (auto node : scc) {
                fout << node << ' ';
            }
            fout << '\n';
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
    auto* task = new (nothrow) Task(); // hint: cppreference/nothrow
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
