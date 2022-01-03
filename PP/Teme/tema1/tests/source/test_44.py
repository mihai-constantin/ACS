def main():
	a = 3

	for x in [1, 2, 3]:
		if x % 2 == 0:
			for y in [3, 2, 1]:
				a += (x + y)

	i = 0
	j = 10
	r = 0
	while i != j:
		i += 1
		j -= 1
		for x in [1, 2, 3]:
			r = (i + j)
			r += x

	if r % 2 == 0:
		for x in [5, 6, 7, 8, 9]:
			r -= x

	if r % 2 != 0:
		x = 5
		while x < 10:
			r -= x
			x += 1
