#include <iostream>
#include <fstream>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(get_result(n, x, y));
    }

private:
    int n, x, y;

    void read_input() {
        ifstream fin("in");
        fin >> n >> x >> y;
        fin.close();
    }

    int calcul(int lin, int col, int lat) {
        int r = 0;
        if (lat == 1) {
            return 1;
        }

        lat /= 2;

        // jumatatea de jos
        if (lin > lat) {
            r += 2 * lat * lat;
            lin = lin - lat;
        }

        // jumatatea din dreapta
        if (col > lat) {
            r += lat * lat;
            col = col - lat;
        }

        return r + calcul(lin, col, lat);
    }

    int get_result(int n, int x, int y) {
        /*
        TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune
        2^n x 2^n
        */
        return calcul(x, y, (1 << n));
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
