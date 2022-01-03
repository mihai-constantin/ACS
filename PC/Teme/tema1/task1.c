// CONSTANTIN MIHAI - 311CD

#include <stdio.h>

int main()
{
	int N, nr, i, j;
	char C, c;

	scanf("%d %c", &N, &C);

	nr = 0; // nr = NR CURENT DE CARACTERE ' ' DE PE O LINIE

	for(i = 1; i <= N; i++)
	{
		c = ' '; // CARACTERUL CURENT CE TREBUIE AFISAT

		for(j = 1; j <= nr; j++)
		{
			printf("%c ", c);
		}

		c = C;

		for(j = nr + 1; j < N; j++)
		{
			printf("%c ", c);
		}

		printf("%c\n", c); // AFISAREA ULTIMULUI CARACTER DE PE LINIA CURENTA + '\n'

		nr++; // NR DE CARACTERE ' ' DE PE LINIA URMATOARE VA CRESTE CU O UNITATE
	}

	return 0;
}