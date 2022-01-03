/**
 * Cel mai mic numar palindrom mai mare sau egal decât un numar dat.
 */
#include <stdio.h>
#include <stdbool.h>

bool palindrom(int x) {
    int aux = x, ogl = 0;
    while(aux) {
        ogl = ogl * 10 + aux % 10;
        aux /= 10;
    }
    return x == ogl;
}

int main()
{
    int x;
    scanf("%d", &x);

    while(!palindrom(x)) {
        x++;
    }
    printf("%d\n", x);
    
    return 0;
}
