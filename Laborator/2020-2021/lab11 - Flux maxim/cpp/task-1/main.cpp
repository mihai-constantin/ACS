#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// numarul maxim de noduri
#define NMAX 1005

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[i] = lista de adiacenta a nodului i
    vector<int> adj[NMAX];
    vector<int> visited;
    vector<int> parent;
    queue<int> q;

    // cap[i][j] = capacitatea arcului i -> j
    int cap[NMAX][NMAX];
    int F[NMAX][NMAX];

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        memset(cap, 0, sizeof cap);
        for (int i = 1, x, y, c; i <= m; i++) {
            // x -> y de capacitate c
            fin >> x >> y >> c;
            adj[x].push_back(y);
            adj[y].push_back(x);

            // Presupunem existenta mai multor arce x -> y cu capacitati c1, c2, ...
            // Comprimam intr-un singur arc x -> y cu capacitate
            // cap[x][y] = c1 + c2 + ...
            cap[x][y] += c;
        }
        fin.close();
    }

    void clear(queue<int> &q) {
        queue<int> empty;
        swap(q, empty);
    }

    bool bfs() {
        int i, x, y;

        clear(q);

        visited.resize(n + 1);
        visited.assign(n + 1, 0);

        parent.resize(n + 1);
        parent.assign(n + 1, -1);

        visited[1] = 1;
        q.push(1);

        while(!q.empty()) {
            x = q.front();
            q.pop();

            // parcurg vecinii y ai lui x
            for (i = 0; i < adj[x].size(); i++) {
                y = adj[x][i];

                if (cap[x][y] != F[x][y] && !visited[y]) {
                    visited[y] = 1;
                    parent[y] = x;
                    q.push(y);
                    if (y == n) {
                        return 1;
                    }
                }
            }
        }

        return 0;
    }

    void print_flux() {
        cout << "===    F   ===\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << F[i][j] << " ";
            }
            cout << '\n';
        }
    }

    int get_result() {
        //
        // TODO: Calculati fluxul maxim pe graful orientat dat.
        // Sursa este nodul 1.
        // Destinatia este nodul n.
        //
        // In adj este stocat graful neorientat obtinut dupa ce se elimina orientarea
        // arcelor, iar in cap sunt stocate capacitatile arcelor.
        // De exemplu, un arc (x, y) de capacitate c va fi tinut astfel:
        // cap[x][y] = c, adj[x] contine y, adj[y] contine x.
        //
        int max_flow = 0, fmin, node;

        // print_flux();
        // cout << "===    cap   ===\n";
        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= n; j++) {
        //         cout << cap[i][j] << " ";
        //     }
        //     cout << '\n';
        // }

        while(bfs()) {
            fmin = INT_MAX;

            node = n;
            while (node != 1) {
                fmin = min(fmin, cap[parent[node]][node] - F[parent[node]][node]);
                node = parent[node];
            }

            node = n;
            while (node != 1) {
                F[parent[node]][node] += fmin;
                F[node][parent[node]] -= fmin;
                node = parent[node];
            }

            max_flow += fmin;

            // print_flux();
            // cout << "max_flow: " << max_flow << '\n';
        }

        return max_flow;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << '\n';
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
