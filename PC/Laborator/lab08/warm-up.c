#include <stdio.h>

void next(void) {
	fflush(stdout);
	getchar();
}

int main(void)
{
	int a[10];

	printf("a[0] = ?"); next();
	printf("a[0] = %d\n", a[0]); next();

	printf("*a = ?"); next();
	printf("*a = %d\n", *a); next();

	printf("a = ?"); next();
	printf("a = %p\n", a); next();

	printf("&a = ?"); next();
	printf("&a = %p\n", &a); next();

	printf("sizeof(a[0]) = ?"); next();
	printf("sizeof(a[0]) = %ld\n", sizeof(a[0])); next();

	printf("sizeof(*a) = ?"); next();
	printf("sizeof(*a) = %ld\n", sizeof(*a)); next();

	printf("sizeof(a) = ?"); next();
	printf("sizeof(a) = %ld\n", sizeof(a)); next();

	printf("sizeof(&a) = ?"); next();
	printf("sizeof(&a) = %ld\n", sizeof(&a)); next();

	printf("*a + 1 = ?"); next();
	printf("*a + 1 = %d\n", *a + 1); next();

	printf("*a + 2 = ?"); next();
	printf("*a + 2 = %d\n", *a + 2); next();

	printf("a + 1 = ?"); next();
	printf("a + 1 = %p\n", a + 1); next();

	printf("a + 2 = ?"); next();
	printf("a + 2 = %p\n", a + 2); next();

	printf("&a + 1 = ?"); next();
	printf("&a + 1 = %p\n", &a + 1); next();

	printf("&a + 2 = ?"); next();
	printf("&a + 2 = %p\n", &a + 2); next();

	return 0;
}
