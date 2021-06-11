#include <iostream>
#include <fstream>
using namespace std;

class Task {
public:
    void solve() {
        read_input();
        print_output(fast_pow(base, exponent, mod));
    }

private:
    int base, exponent, mod;

    void read_input() {
        ifstream fin("in");
        fin >> base >> exponent >> mod;
        fin.close();
    }

    int fast_pow(int base, int exponent, int mod) {
        // TODO: Calculati (base ^ exponent) % mod in O(log exponent)
        int ans = 1;
        while(exponent != 0) {
            if (exponent % 2 == 1) {
                ans = (1LL * (ans % mod) * (base % mod)) % mod;
            }
            base = (1LL * (base % mod) * (base % mod)) % mod;
            exponent /= 2;
        }
        return ans;
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
