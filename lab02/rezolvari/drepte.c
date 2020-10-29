/**
 * Determinarea concurentei a doua drepte in plan.
 */

#include <stdio.h>

int main()
{
    double a1, b1, c1, a2, b2, c2;
    scanf("%lf %lf %lf", &a1, &b1, &c1);
    scanf("%lf %lf %lf", &a2, &b2, &c2);

    if (a1/a2 == b1/b2 && b1/b2 == c1/c2) {
        printf("Cele doua linii coincid.\n");
    } else if ((a1 == a2 && !a1) || (b1 == b2 && !b1) || a1/a2 == b1/b2) {
        printf("Cele doua linii sunt paralele.\n");
    } else {
        double x = (b1 * c2 - b2 * c1) / (a1 * b2 - a2 * b1);
        double y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
        printf("Punctul de intersectie: %lf %lf\n", x, y);
    }

    return 0;
}