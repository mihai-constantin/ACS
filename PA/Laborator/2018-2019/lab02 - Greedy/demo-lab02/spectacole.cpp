#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <limits.h>

using namespace std;

bool end_hour_comp (pair<int, int>& e1, pair<int, int>& e2) {
    // comparam doar dupa pozitii, tag-ul este folosit doar la identificare
    return (e1.second < e2.second);
}

vector<pair<int, int>> plan(vector<pair<int, int> >& intervals) {
    vector<pair<int, int>> plan;
    // se sorteaza intervalele pe baza orei de sfarsit a spectacolelor
    sort(intervals.begin(), intervals.end(), end_hour_comp);

    // se ia ultimul spectacol ca terminat la -oo pt a putea incepe cu
    // cel mai devreme
    int last_end = INT_MIN;
    for (auto interval : intervals) {
        // daca inceputul intervalului curent este dupa sfarsitul ultimului
        // spectacol (last_end) il adaugam in lista de spectacole la care
        // se participa
        if (interval.first >= last_end)
        {
            plan.push_back(interval);
            // dupa ce am adaugat un spectacol, updatam ultimul sfarsit de spectacol
            last_end = interval.second;
        }
    }
    return plan;
}

int main() {
    vector<pair<int, int>> intervals;
    intervals.push_back(make_pair(5, 10));
    intervals.push_back(make_pair(14, 17));
    intervals.push_back(make_pair(8, 13));
    intervals.push_back(make_pair(13, 15));
    intervals.push_back(make_pair(15, 17));
    intervals.push_back(make_pair(3, 6));
    intervals.push_back(make_pair(4, 7));
    intervals.push_back(make_pair(6, 9));
    intervals.push_back(make_pair(11, 14));
    intervals.push_back(make_pair(10, 11));


    vector<pair<int, int>> planned_intervals = plan(intervals);
    for (auto spectacle : planned_intervals) {
        cout << "(" << spectacle.first << " " << spectacle.second << ")";
    }
    cout << "\n";
}
