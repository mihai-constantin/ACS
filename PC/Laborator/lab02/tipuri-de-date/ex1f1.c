#include <stdio.h>

int main()
{
    char x = -1;
	int y = x;
 
    // overflow -> afiseaza 4294967295
	printf("%u\n", x);
	printf("%u\n", y); 
 
	char a = 1;
	int b = a;
 
	printf("%u\n", a);
	printf("%u\n", b);

    return 0;
}