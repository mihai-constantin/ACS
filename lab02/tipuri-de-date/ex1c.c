#include <stdio.h>

int main()
{
    unsigned char x = 130; // x apartine intervalului [0, 255]
 
	if (x > 0)
		printf("I'm positive!\n");
	else
		printf("Not sure...\n");

    return 0;
}