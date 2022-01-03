def main():
	a = 9
	b = 16
	x = prod(a, 2)
	y = prod(b, 2)
	s = x + y
	c = 9 + 6
	z = prod(c, 3)
	s += z
	s += prod(100, 2)
	s2 = prod(2, 5) + prod(3, 4)
	s2 += 10
	w = prod(2, 7)
	s3 = prod(8, 2)
	s4 = prod(159, 2)
	s5 = 0
	if s4 % 3 == 0:
		s5 += prod(18, 2)
	if s5 > 0:
		s5 -= prod(13, 2)
	for i in [1, 2, 3]:
		s5 += i
		if i % 2 == 0:
			s5 += prod(25, 2)
