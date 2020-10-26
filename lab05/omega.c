#include <stdio.h>
#include <stdbool.h>

bool arr[10];

int main()
{
	int bits, input, output;
	printf("Number of bits: ");
	scanf("%d", &bits);
	printf("input: ");
	scanf("%d", &input);
	printf("output: ");
	scanf("%d", &output);

	int res = input^output;

	int idx = 0;
	while(res) {
		arr[idx++] = res % 2;
		res /= 2;
	}

	for (int i = bits - 1; i >= 0; i--) {
		if (!arr[i]) {
			printf("direct ");
		} else {
			printf("invers ");
		}
	}
	printf("\n");

	return 0;
}
