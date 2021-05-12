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
    struct Edge {
        int x;
        int y;

        Edge() { }
        Edge(int x, int y)
            : x(x)
            , y(y) { }
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

    vector<int> visited;
    vector<int> parent;

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

    void tarjan(vector<Edge> &sol, int x) {
        int i, y;
        Edge edge;
        
        idx[x] = lowlink[x] = indecs++;
        visited[x] = 1;

        // parcurg vecinii y ai lui x
        for (i = 0; i < adj[x].size(); i++) {
            y = adj[x][i];

            if (!visited[y]) {
                parent[y] = x;
                tarjan(sol, y);

                lowlink[x] = min(lowlink[x], lowlink[y]);

                if (lowlink[y] > idx[x]) {
                    //  cout << "edge: " << x << " " << y << '\n';
                    edge.x = x;
                    edge.y = y;
                    sol.push_back(edge);
                }
            } else if (parent[x] != y) {
                lowlink[x] = min(lowlink[x], idx[y]);
            }
        }
    }

    vector<Edge> get_result() {
        //
        // TODO: Gasiti toate muchiile critice ale grafului neorientat stocat cu liste de adiacenta in adj.
        //
        // Rezultatul se va returna sub forma unui vector cu toate muchille critice (ordinea lor nu conteaza).
        //
        // Indicație: Folosiți algoritmul lui Tarjan pentru CE.
        //

        int i;
        vector<Edge> all_ces;

        idx.resize(n + 1);
        lowlink.resize(n + 1);

        visited.resize(n + 1);
        visited.assign(n + 1, 0);

        parent.resize(n + 1);
        parent.assign(n + 1, -1);

        tarjan(all_ces, 1);

        // cout << "idx\n";
        // for (i = 1; i <= n; i++) {
        //     cout << idx[i] << " ";
        // }
        // cout << '\n';

        // cout << "lowlink\n";
        // for (i = 1; i <= n; i++) {
        //     cout << lowlink[i] << " ";
        // }
        // cout << '\n';

        // cout << "parent\n";
        // for (i = 1; i <= n; i++) {
        //     cout << parent[i] << " ";
        // }
        // cout << '\n';

        // cout << "visited\n";
        // for (i = 1; i <= n; i++) {
        //     cout << visited[i] << " ";
        // }
        // cout << '\n';

        return all_ces;
    }

    void print_output(const vector<Edge>& all_ces) {
        ofstream fout("out");
        fout << all_ces.size() << '\n';
        for (auto& ce : all_ces) {
            fout << ce.x << ' ' << ce.y << '\n';
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
