#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(compute_sqrt());
    }

private:
    double n;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        fin.close();
    }

    double compute_sqrt() {
        /*
        TODO: Calculati sqrt(n) cu o precizie de 0.001
        Precizie de 10^-x = |rezultatul vostru - rezultatul corect| <= 10^-x
        */

        int st = 0;
        int dr = n;
        double res;
        while (st <= dr) {
            int m = (st + dr) / 2;
            if (m * m == n) {
                res = m;
                break;
            }
            if (m * m < n) {
                res = m;
                st = m + 1;
            } else {
                dr = m - 1;
            }
        }

        double increment = 0.1;
        int precision = 3;
        for (int i = 0; i < precision; i++) {
            while(res * res <= n) {
                res += increment;
            }
            res -= increment;
            increment /= 10;
        }

        return res;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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
