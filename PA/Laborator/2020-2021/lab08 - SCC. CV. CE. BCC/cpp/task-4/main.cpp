#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cmath>
#include <set>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    struct Edge {
        int x;
        int y;

        Edge() { }
        Edge(int x, int y)
            : x(x)
            , y(y) { }

        bool operator==(const Edge& other) { return x == other.x && y == other.y; }
        bool operator!=(const Edge& other) { return !(*this == other); }
    };

    // numarul maxim de noduri
    static constexpr int NMAX = (int)1e5 + 5; // 10^5 + 5 = 100.005

    // n = numar de noduri, m = numar de muchii/arce
    int n, m;

    // adj[node] = lista de adiacenta a nodului node
    // exemplu: daca adj[node] = {..., neigh, ...} => exista arcul (node, neigh)
    vector<int> adj[NMAX];

    vector<int> idx;
    vector<int> lowlink;
    stack <Edge> stk;

    set<int> con;
    
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

    void tarjan(vector<vector<int>> &all_bccs, int x) {
        int i, y;

        idx[x] = lowlink[x] = indecs++;

        // parcurgem vecinii y ai lui x
        for (i = 0; i < adj[x].size(); i++) {
            y = adj[x][i];

            if (idx[y] == -1) {
                stk.push(Edge(x, y));
                tarjan(all_bccs, y);
                lowlink[x] = min(lowlink[x], lowlink[y]);
                if (lowlink[y] >= idx[x]) {
                    con.clear();
                    int tx, ty;
                    do {
                        tx = stk.top().x;
                        ty = stk.top().y;
                        stk.pop();
                        con.insert(tx);
                        con.insert(ty);
                    } while (tx != x || ty != y);
                    vector<int> _con{con.begin(), con.end()};
                    all_bccs.push_back(_con);
                }
            } else {
                lowlink[x] = min(lowlink[x], idx[y]);
            }
        }
	}

    vector<vector<int>> get_result() {
        //
        // TODO: Găsiți componentele biconexe (BCC) ale grafului neorientat cu n noduri, stocat în adj.
        //
        // Rezultatul se va returna sub forma unui vector, fiecare element fiind un BCC (adică tot un vector).
        // * nodurile dintr-un BCC pot fi găsite în orice ordine
        // * BCC-urile din graf pot fi găsite în orice ordine
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru BCC.
        //

        vector<vector<int>> all_bccs;

        idx.resize(n + 1);
        idx.assign(n + 1, -1);

        lowlink.resize(n + 1);

        for (int i = 1; i <= n; i++) {
            if (idx[i] == -1) {
                tarjan(all_bccs, i);
            }
        }

        return all_bccs;
    }

    void print_output(const vector<vector<int>>& all_bccs) {
        ofstream fout("out");
        fout << all_bccs.size() << '\n';
        for (auto& bcc : all_bccs) {
            for (auto node : bcc) {
                fout << node << " ";
            }
            fout << "\n";
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
