#include <stdio.h>

int sum_recursive(int n) {
	if (!n) {
		return 0;
	}
	return n % 10 + sum_recursive(n / 10);
}

int sum_recursive_odd_digits(int n) {
	if (n < 10) {
		if (n % 2 == 1) {
			return n;
		}
		return 0;
	}
	if (n % 2 == 1) {
		return n % 10 + sum_recursive_odd_digits(n / 10);
	}
	return sum_recursive_odd_digits(n / 10);
}

int get_last_odd_digit_recursive(int n) {
	if (n < 10) {
		if (n % 2 == 1) {
			return n;
		}
		return 0;
	}
	if (n % 2 == 1) {
		return n % 10;
	}
	return get_last_odd_digit_recursive(n / 10);
}

int sum_iterative(int n) {
	int s = 0;
	while(n) {
		s += n % 10;
		n /= 10;
	}
	return s;
}

int main(void)
{
	int nr;
	scanf("%d", &nr);
	printf("%d\n", sum_recursive(nr));
	printf("%d\n", sum_iterative(nr));
	printf("%d\n", sum_recursive_odd_digits(nr));
	printf("%d\n", get_last_odd_digit_recursive(nr));

	return 0;
}
