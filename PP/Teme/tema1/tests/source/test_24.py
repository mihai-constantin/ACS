def main():
	a = 2
	b = 3
	c = 5

	f = 20
	g = 21
	h = 22
	j = 23

	x1 = (f % a) + b
	x2 = (g - a) % b
	x3 = h % c
	x4 = j % b

	y1 = (a + f) % b
	y2 = g % a

	z1 = a + x1
	z2 = y1 + y2

	w1 = y1 - y2
