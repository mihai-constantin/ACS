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

	if ((a + b) - (c - a)) % 2 == 0:
		c = 10

	if ((a + b) - (c - a)) % 2 != 0:
		c += 1

	d = 7
	d += (a + b)

	d -= 2

	if d % 2 == 0:
		d += 1
