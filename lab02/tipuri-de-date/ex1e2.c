#include <stdio.h>

int main()
{
    unsigned int x = ~0;
 
	printf("%d\n", x); // afisez ca intreg(simplu) -> in loc de 4294967295 se afiseaza -1
	printf("%d\n", x + 1); // afiseaza 0

    return 0;
}