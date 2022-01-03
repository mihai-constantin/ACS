/**
 * SO, 2016
 * Lab #1, Introduction
 *
 * Task #4, Linux
 *
 * Debugging with gdb
 */


#include <stdio.h>

#define ARRAY_MAX_SIZE 8192

void print_array(int v[], int n)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("%d ", v[i]);
		if (i != 0 && i % 11 == 0)
			printf("\n");
	}
}

double inv_sum(int v[], int n)
{
	int i;
	double isum = 0;

	for (i = 0; i < n; i++) {
		if(v[i] != 0) {
			isum += 1.0/v[i];
		}
	}

	return isum;
}

void show_inv(int v[], int n)
{
	printf("Inverses sum for: [ ");

	print_array(v, n);

	printf("] is: %f\n", inv_sum(v, n));
}

int main(void)
{
	int v[] = { 4, 3, 0, 3, 2};

	show_inv(v, 5);

	return 0;
}

