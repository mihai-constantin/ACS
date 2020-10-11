#include <stdio.h>

int main()
{
    char x = 321; // overflow

    /*
        128 -> -128
        129 -> -127
        ...
        0 -> 256
        ...
        65 -> 321
    */
 
	printf("%u\n", x);
	printf("%c\n", x);
	printf("%d\n", x);

    return 0;
}