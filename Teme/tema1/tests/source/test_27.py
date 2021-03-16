def main():
	a = 20
	b = 20

	if a != b:
		a += 1
		b -= 1

	if b != 20:
		b = a
		a = b
