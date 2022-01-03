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
        if ( (*f)(v[i]) == 1 ) {
            nr++;
        }
    }
    printf("%d\n", nr);
}

int main()
{
    int n;
	scanf("%d", &n);
	int *v = (int *) malloc (n * sizeof(int)); // aloc un vector de n elemente de tip intreg

	for(int i = 0; i < n; i++) {
		// scanf("%d", &v[i]);
        // v[i] <=> *(v + i)
        scanf("%d", v + i); 
	}

    // for(int i = 0; i < n; i++) {
	// 	printf("%d ", *(v + i));
	// }
    // printf("\n");

    // determina cate numere pare am in vector
	count_even_numbers(even, v, n);

    // dezaloc memoria
    free(v);

	return 0;
}
