//
// CONSTANTIN MIHAI - 321CD
//

#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int x, int y) {
    return x > y;
}

void Base_Case(vector<vector<int>> &d, vector<int> v, int idx) {

    priority_queue<int> priorityQueue;
    for (int i = 1; i <= idx; i++) {
        priorityQueue.push(v[i]);
    }

    // initial score for both players
    int score_player1 = priorityQueue.top();
    int score_player2 = 0;
    priorityQueue.pop();

    // initial difference between scores
    int max_diff = score_player1;

    /**
     * turn = 0 -> Tuzgu's turn
     * turn == 1 -> Ritza's turn
     */

    int turn = 1;

    while (!priorityQueue.empty()) {
        if (turn == 1) {
            score_player2 = priorityQueue.top();
            max_diff = max_diff - score_player2;
            turn = 0;
        } else {
            score_player1 = priorityQueue.top();
            max_diff = max_diff + score_player1;
            turn = 1;
        }
        priorityQueue.pop();
    }

    d[idx][0] = max_diff;
}

int main() {

    FILE *in, *out;

    in = fopen("p2.in", "r");
    out = fopen("p2.out", "w");

    int N, K, x;
    fscanf(in, "%d %d", &N, &K);

    vector<int> v;
    v.push_back(-1); // index starts from 1
    for (int i = 0; i < N; i++) {
        fscanf(in, "%d", &x);
        v.push_back(x);
    }

    // sort v in descending order
    sort(v.begin() + 1, v.end() + 1, cmp);

    /**
     * DP
     * d[i][j] = maximum difference Tuzgu can obtain from first i elements from v, removing j elements
     */

    vector<vector<int>> d(N + 1, vector<int>(K + 1, 0));

    /**
     * d[i][0] -> normal game. No element is removed from initial array.
     */

    for (int idx = 1; idx <= N; idx++) {
        Base_Case(d, v, idx);
    }

    /**
     * i = 2 : N, j = 1 : i - 1
     * d[i][j] = max(d[i - 1][j - 1], d[i - 1][j] + v[i]), If (i - j) % 2 == 1
     * d[i][j] = max(d[i - 1][j - 1], d[i - 1][j] - v[i]), If (i - j) % 2 == 0
     */

    int j_stop;
    for (int i = 2; i <= N; i++) {
        j_stop = min(i, K + 1);
        for (int j = 1; j < j_stop; j++) {
            if ((i - j) & 1) {
                d[i][j] = max(d[i - 1][j - 1], d[i - 1][j] + v[i]);
            } else {
                d[i][j] = max(d[i - 1][j - 1], d[i - 1][j] - v[i]);
            }
        }
    }

    fprintf(out, "%d\n", d[N][K]);

    return 0;
}

