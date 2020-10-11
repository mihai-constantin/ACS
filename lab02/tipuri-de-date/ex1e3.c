#include <stdio.h>

int main()
{
    int x = ~0; // 32 de biti de 1 
    /**
     * Valoarea maxima pentru x este de 2^31 - 1, deci noi avem 32 de biti de 1 -> overflow 
     */
	printf("%d\n", x); // overflow -> -1
	printf("%u\n", x); // 4294967295
	printf("%u\n", x + 1); // 0

    return 0;
}