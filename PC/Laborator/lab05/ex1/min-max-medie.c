/**
 * Exercitiul 1. 
 * Determinarea elementului minim, pozitiei elementului maxim, media aritmetica din vector, cat si numarul de elemente mai mari decat aceasta.
 */
#include <stdio.h>

#define N 100
#define epsilon 0.000001

void read_array(int v[N], int n) {
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
}

void get_min(int v[N], int n) {
    int minim = v[0];
    int i;
    for (i = 1; i < n; i++) {
        if (minim > v[i]) {
            minim = v[i];
        }
    }
    printf("min = %d\n", minim);
}

void get_pos_max(int v[N], int n) {
    int maxim = v[0];
    int pos = 0;
    int i;
    for (i = 1; i < n; i++) {
        if (maxim < v[i]) {
            maxim = v[i];
            pos = i;
        }
    }
    printf("pos_max = %d\n", pos);
}

double get_ma(int v[N], int n) {
    int i;
    long long s = 0;
    double ma;
    for (i = 0; i < n; i++) {
        s += v[i];
    }
    ma = (double)s / n;
    return ma;
}

void gt_ma(int v[N], int n, double ma) {
    int i, nr = 0;
    for (i = 0; i < n; i++) {
        if ((double)v[i] - ma > epsilon) {
            nr++;
        }
    }
    printf("gt_ma = %d\n", nr);
}

int main()
{
    int v[N], n;

    scanf("%d", &n);
    read_array(v, n);

    get_min(v, n);
    get_pos_max(v, n);
    double ma = get_ma(v, n);
    printf("ma = %.2lf\n", ma);
    gt_ma(v, n, ma);

    return 0;
}
