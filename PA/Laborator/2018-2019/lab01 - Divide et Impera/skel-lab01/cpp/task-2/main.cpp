#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

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
        int precision = 3;
        int start = 0;
        int end = n;
        int mid;
        float ans;

        while (start <= end) {
            mid = (start + end) / 2;

            if (mid * mid == n) {
                ans = mid;
                break;
            }

            if (mid * mid < n) {
                start = mid + 1;
                ans = mid;
            } else {
                end = mid - 1;
            }
        }

        float increment = 0.1;
        for (int i = 0; i < precision; i++) {
            while (ans * ans <= n) {
                ans += increment;
            }

            ans = ans - increment;
            increment = increment / 10;
        }

        return ans;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
        fout.close();
    }
};

int main() {
    Task task;
    task.solve();
    return 0;
}
