//
// CONSTANTIN MIHAI - 321CD
//

#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main() {

    FILE *in, *out;

    in = fopen("p1.in", "r");
    out = fopen("p1.out", "w");

    int N, x;
    fscanf(in, "%d", &N);

    // use a max heap to access the maximum element in constant time
    priority_queue<int> priorityQueue;

    for (int i = 0; i < N; i++) {
        fscanf(in, "%d", &x);
        priorityQueue.push(x);
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

    fprintf(out, "%d\n", max_diff);

    return 0;
}