def main():
	s = 0
	for x in range(10):
		for y in range(10):
			if y % 2 == 0:
				for z in range(5):
					if z % 2 == 0:
						s += x
					for w in range(3):
						if w % 2 != 0:
							s += x
						if w % 2 == 0:
							s += y

