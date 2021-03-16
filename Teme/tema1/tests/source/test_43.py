def main():
	a = 3

	for x in [1, 2, 3]:
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
