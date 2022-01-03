def main():
	a = 5
	b = 7

	if a > b:
		b = a
		c = 20

	if a < b:
		b = a
		c = 10

	d = a + b
	d += 5

	if (d % 2) == 0:
		d -= 3

	if (d % 2) != 0:
		d %= 3

	e = c + d
	f = a + b

	if e > f:
		f = e

