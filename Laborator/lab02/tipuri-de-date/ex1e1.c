#include <stdio.h>

int main()
{
    unsigned int x = ~0;
 
	printf("%u\n", x); // toti bitii 1 -> valoare maxima pentru unsigned int: 4294967295
	printf("%u\n", x + 1); // overflow -> revine la 0

    return 0;
}