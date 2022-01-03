def main():
	s = 0
	x1 = range(5)
	x2 = range(10)

	for x in x1:
		for y in x2:
			s += x
			s += y

	z = range(s)
