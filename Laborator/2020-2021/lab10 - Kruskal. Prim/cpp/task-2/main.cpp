#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// numarul maxim de noduri
#define NMAX 200005

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result());
    }

private:
    // n = numar de noduri, m = numar de muchii
    int n, m;

    // adj[i] = lista de adiacenta a lui i
    // (j, w) - exista muchie de la i la j de cost w
    vector<pair<int, int>> adj[NMAX];
    priority_queue<pair<int, int>> H;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 1, x, y, w; i <= m; i++) {
            fin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
        fin.close();
    }

    int get_result() {
        //
        // TODO: Calculati costul minim al unui arbore de acoperire
        // folosind algoritmul lui Prim.
        //

        int i, x, y, cost;

        vector<int> d(n + 1, NMAX);
        vector<int> visited(n + 1, 0);
        vector<int> parent(n + 1, -1);

        // introduc in heap nodul de start
        H.push(make_pair(0, 1));
        d[1] = 0;

        while(!H.empty()) {

            while(!H.empty() && visited[H.top().second]) {
                H.pop();
            }

            if (H.empty()) {
                break;
            }

            x = H.top().second;
            visited[x] = 1;

            // parcurg vecinii y ai lui x
            for (i = 0; i < adj[x].size(); i++) {
                y = adj[x][i].first;
                cost = adj[x][i].second;

                if (d[y] > cost && !visited[y]) {
                    parent[y] = x;
                    d[y] = cost;
                    H.push(make_pair(-d[y], y));
                }
            }
        }

        cost = 0;
        for (int i = 1; i <= n; i++) {
            // printf("[%d] %d %d\n", i, d[i], parent[i]);
            if (parent[i] != -1) {
                cost += d[i];
            }
        }

        return cost;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result << "\n";
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
