def main():
	a = 9
	b = 16
	x = sqrt(a)
	y = sqrt(b)
	s = x + y
	c = 9 + 6
	c = c + 10
	z = sqrt(c)
	s += z
	s += sqrt(100)
	s2 = sqrt(81) + sqrt(36)
	s2 += 10
	w = sqrt(s2)
	s3 = sqrt(64)
	s4 = sqrt(25281)
	s5 = 0
	if s4 % 3 == 0:
		s5 += sqrt(324)
	if s5 > 0:
		s5 -= sqrt(196)
	for i in [1, 2, 3]:
		s5 += i
		if i % 2 == 0:
			s5 += sqrt(625)
