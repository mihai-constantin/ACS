/**
 * Determinarea diferentei dintre 2 intervale orare.
 */

#include <stdio.h>

int main()
{
    int hh1, mm1, ss1, hh2, mm2, ss2;
    printf("Enter the first interval in hh:mm:ss format: ");
    scanf("%d:%d:%d", &hh1, &mm1, &ss1);

    printf("Enter the second interval in hh:mm:ss format: ");
    scanf("%d:%d:%d", &hh2, &mm2, &ss2);

    int hh = hh2 - hh1;
    int mm = mm2 - mm1;
    int ss = ss2 - ss1;
    if (ss < 0) {
        ss += 60;
        mm--;
    }
    if (mm < 0) {
        mm += 60;
        hh--;
    }
    if (hh < 0) {
        hh += 24;
    }

    printf("Time between intervals: %d:%d:%d\n", hh, mm, ss);

    return 0;
}