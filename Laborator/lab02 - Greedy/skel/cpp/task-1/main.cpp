#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Object {
    int weight;
    int price;

    Object(int _weight, int _price) : weight(_weight), price(_price) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

    static bool cmp(Object obj1, Object obj2) {
        return ((double)obj1.price / obj1.weight) > ((double)obj2.price / obj2.weight);
    }

 private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    double get_result() {
        // TODO: Aflati profitul maxim care se poate obtine cu obiectele date.
        
        // sortare descrescatoare dupa pi/wi
        sort(objs.begin(), objs.end(), cmp);

        double profit = 0;
        vector<Object>::iterator it;
        for(it = objs.begin(); it != objs.end() && w; ++it) {
            if ((*it).weight <= w) { // iau tot obiectul
                profit += (*it).price;
                w -= (*it).weight;
            } else { // iau o fractiune din obiect
                profit += (double)(*it).price / (*it).weight * w;
                w = 0;
            }
        }

        return profit;
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
