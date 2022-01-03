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
    int n, x;
    vector<int> v;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, e; i < n; i++) {
            fin >> e;
            v.push_back(e);
        }
        fin >> x;
        fin.close();
    }

    int find_first() {
        /*
        TODO 1: Cautati prima pozitie pe care se afla valoarea x
        In cazul in care x nu apare in sir, returnati -1
        */
        int res = -1;

        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int m = (left + right) / 2;
            if(v[m] >= x) {
                res = m;
                right = m - 1;
            } else {
                left = m  + 1;
            }
        }

        return res;
    }

    int find_last() {
        /*
        TODO 2: Cautati ultima pozitie pe care se afla valoarea x
        In cazul in care x nu apare in sir, returnati -1
        */

        int res = -1;

        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int m = (left + right) / 2;
            if(v[m] <= x) {
                res = m;
                left = m + 1;
            } else {
                right = m  - 1;
            }
        }

        return res;
    }

    int get_result() {
        // TODO 3: Calculati numarul de aparitii ale lui x in vectorul v
        int first_pos = find_first();
        int last_pos = find_last();
        if (first_pos == -1 || last_pos == -1) {
            return 0;
        }
        return last_pos - first_pos + 1;
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
