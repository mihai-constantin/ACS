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
    int n, m;
    vector<int> dist;

    void read_input() {
        ifstream fin("in");
        fin >> n >> m;
        for (int i = 0, d; i < n; i++) {
            fin >> d;
            dist.push_back(d);
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati numarul minim de opriri necesare pentru a ajunge
        la destinatie.
        */
        int stops = 0;
        int range = m;
        for(int i = 0; i < n - 1; i++) {
            range -= (i != 0) ? dist[i] - dist[i - 1] : dist[i];
            if (dist[i + 1] - dist[i] > range) {
                // alimentare la statia i
                stops++;
                range = m;
            }
        }
        return stops;
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
