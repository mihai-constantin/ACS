#include <stdio.h>

int main()
{
    char x = 130; // overflow -> x = -126
    printf("%d\n", x);
 
	if (x > 0)
		printf("I'm positive!\n");
	else
		printf("Not sure...\n");
    return 0;
}