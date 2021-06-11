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
    int n, k;
    string caractere;
    vector<int> freq;

    void read_input() {
        ifstream fin("in");
        fin >> n >> k;
        fin >> caractere;
        caractere = " " + caractere; // Adaugare element fictiv -
                                     // indexare de la 1.
        freq.push_back(-1); // Adaugare element fictiv - indexare de la 1.
        for (int i = 1, f; i <= n; i++) {
            fin >> f;
            freq.push_back(f);
        }
        fin.close();
    }

    bool validation(vector<char> &solution, int step, int idx) {
        int nr = 0;
        while(step >= 0 && solution[step] == caractere.at(idx)) {
            step--;
            nr++;
        }
        if (nr >= k ) {
            return false;
        }
        return true;
    }

    void bkt(int step, int stop,  vector<char> &solution, vector<vector<char>> &all) {
        if (step == stop) {
            all.push_back(solution);
            return;
        }

        for (int i = 1; i <= n; i++) {
            if (freq[i] && validation(solution, step - 1, i)) {
                solution[step] = caractere.at(i);
                freq[i]--;
                bkt(step + 1, stop, solution, all);
                freq[i]++;
            }
        }
    }

    vector<vector<char>> get_result() {
        vector<vector<char>> all;

        // TODO: Construiti toate sirurile cu caracterele in stringul caractere
        // (indexat de la 1 la n), si frecventele in vectorul freq (indexat de la 1 la n),
        // stiind ca nu pot fi mai mult de K aparitii consecutive ale
        // aceluiasi caracter.
        //
        // Pentru a adauga un nou sir:
        //     vector<char> sir;
        //     all.push_back(sir);
        //

        int length = 0;
        for (int i = 1; i <= n; i++) {
            length += freq[i];
        }
        vector<char> solution(length);
        
        bkt(0, length, solution, all);

        return all;
    }

    void print_output(const vector<vector<char>>& result) {
        ofstream fout("out");
        fout << result.size() << '\n';
        for (size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                fout << result[i][j];
            }
            fout << '\n';
        }
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
    auto* task = new (std::nothrow) Task{}; // hint: cppreference/nothrow
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
