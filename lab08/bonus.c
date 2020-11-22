/**
 * Exemplu utilizare pointer la functie
 */

#include <stdio.h>
#include <stdlib.h>

int even(int x) {
    return !(x & 1);
}

void count_even_numbers(int (*f)(int), int *v, int n) {
    int nr = 0;
	for (int i = 0; i < n; i++) {
        if ((*f)(v[i])) {
            nr++;
        }
    }
    printf("%d\n", nr);
}

int main()
{
    int n;
	scanf("%d", &n);
	int *v = (int*) malloc (n * sizeof(int));

	for(int i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}

	count_even_numbers(even, v, n);

	return 0;
}