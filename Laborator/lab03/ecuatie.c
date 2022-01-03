/**
 * Exercitiul 3.
 * f(x) = ax^2+bx+c, f: [u, v] -> [minim, maxim]
 */
#include <stdio.h>
#include <math.h>

int main()
{
    int a, b, c, u, v;
    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d", &u, &v);

    int delta = b * b - 4 * a * c;
    double x1 = (-b - sqrt(delta))/2 * a;
    double x2 = (-b + sqrt(delta))/2 * a;

    int f_u = a * u * u + b * u + c;
    int f_v = a * v * v + b * v + c;

    printf("f(u) = %d\n", f_u);
    printf("f(v) = %d\n", f_v);

    int maxim, minim;
    if (f_u < f_v) {
        minim = f_u;
        maxim = f_v;
    } else {
        minim = f_v;
        maxim = f_u;
    }

    printf("maxim = %d\n", maxim);
    printf("minim = %d\n", minim);

    if (x1 >= u && x1 <= v) {
        printf("x1 = %lf\n", x1);
    }
    if (x2 >= u && x2 <= v) {
        printf("x2 = %lf\n", x2);
    }

    return 0;
}
