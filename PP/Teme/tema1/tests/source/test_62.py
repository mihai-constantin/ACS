def main():
	a = 9
	b = 3
	c = 4
	d = 5
	x = prod(a, b, c, d)
	y = prod(x, 2, 3, 4, 5, 6)
	z = x + y
	if z % 2 == 0:
		w = prod(1, 2, 3, 4)
	p = 1
	i = 1
	while i < 5:
		p = prod(p, i)
		i += 1
