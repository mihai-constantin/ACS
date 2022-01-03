/**
 * Exercitiul 1.
 * Determinarea numarului din intervalul [2, N] care are suma divizorilor nebanali maxima.
 */
#include <stdio.h>

int main()
{
    int N, i, j, s, s_max = -1, maxim;
    scanf("%d", &N);
    for (i = 2; i <= N; i++) {
        s = 0;
        // calculez suma divizorilor nebanali pentru i
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                // j e divizor pentru i
                s += j;
            }
        }

        if (s > s_max) {
            s_max = s;
            maxim = i;
        }
    }

    printf("%d %d\n", maxim, s_max);

    return 0;
}