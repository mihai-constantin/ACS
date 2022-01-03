def main():
	a = 10
	b = 20

	c = a + b

	if a > 10:
		c += 5

	if (a % 5) > 3:
		c += 6

	if (c - a) > (a + b):
		c += 7

	if a % 2 != 0:
		a += 1

	if b % 2 != 0:
		b += 1

	if c % 2 == 0:
		c += 1
