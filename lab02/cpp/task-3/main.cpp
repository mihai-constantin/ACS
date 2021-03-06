#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Homework {
    int deadline;
    int score;

    Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

    static bool cmp(Homework hw1, Homework hw2) {
        if (hw1.deadline == hw2.deadline) {
            return hw1.score < hw2.score;
        }
        return hw1.deadline < hw2.deadline;
    }

 private:
    int n;
    vector<Homework> hws;

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++) {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati punctajul maxim pe care il puteti obtine planificand
        optim temele.
        */
        // sortare crescatoare dupa dl si crescatoare dupa punctaj
        sort(hws.begin(), hws.end(), cmp);

        int score = hws[hws.size() - 1].score;
        hws[hws.size() - 1].score = -1;
        for(int week = hws[hws.size() - 1].deadline - 1; week > 0; week--) {
            // cout << "week " << week << ": ";
            int current_score = 0;
            int pos = -1;

            for (int i = hws.size() - 2; i >= 0; i--) {
                if (hws[i].deadline < week) {
                    break;
                }
                if (hws[i].score != -1 && current_score < hws[i].score) {
                    current_score = hws[i].score;
                    pos = i;
                }
            }

            if (current_score != 0) {
                score += current_score;
                hws[pos].score = -1;
            }
            
            // cout << current_score << '\n';
        }

        // cout << "score: " << score << '\n';
        
        return score;
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
