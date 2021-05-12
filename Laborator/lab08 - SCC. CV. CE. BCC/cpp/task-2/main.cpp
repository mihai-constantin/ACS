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
    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    vector<int> idx;
    vector<int> lowlink;
    vector<int> visited;
    vector<int> parent;
    vector<int> ap;
    int indecs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y; i <= m; i++) {
            fin >> x >> y; // muchia (x, y)
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        fin.close();
    }

    void tarjan(int x) {
        int i, y, children;

        children = 0;
        idx[x] = lowlink[x] = indecs++;
        visited[x] = 1;

        // parcurg vecinii y ai lui x
        for (int i = 0; i < adj[x].size(); i++) {
            y = adj[x][i];

            if (!visited[y]) {
                children++;
                parent[y] = x;
                tarjan(y);

                lowlink[x] = min(lowlink[x], lowlink[y]);

                if (parent[x] == -1 && children > 1) {
                    ap[x] = 1;
                }

                if (parent[x] != -1 && lowlink[y] >= idx[x]) {
                    ap[x] = 1;
                }
            } else if (parent[x] != y) {
                lowlink[x] = min(lowlink[x], idx[y]);
            }
        }
    }

    vector<int> get_result() {
        //
        // TODO: Gasiti toate nodurile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
        // Rezultatul se va returna sub forma unui vector cu toate punctele critice (ordinea nu conteaza).
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru CV.
        //

        vector<int> all_cvs;

        idx.resize(n + 1);
        lowlink.resize(n + 1);

        ap.resize(n + 1);
        ap.assign(n + 1, 0);

        parent.resize(n  + 1);
        parent.assign(n + 1, -1);

        visited.resize(n + 1);
        visited.assign(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                tarjan(i);
            }
        }

        for (int i = 1; i <= n; i++) {
            if (ap[i]) {
                all_cvs.push_back(i);
            }
        }

        return all_cvs;
    }

    void print_output(const vector<int>& all_cvs) {
        ofstream fout("out");
        for (auto cv : all_cvs) {
            fout << cv << ' ';
        }
        fout << '\n';
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
