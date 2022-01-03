"""
	Bonus task: load all the available coffee recipes from the folder 'recipes/'
	File format:
		first line: coffee name
		next lines: resource=percentage

	info and examples for handling files:
		http://cs.curs.pub.ro/wiki/asc/asc:lab1:index#operatii_cu_fisiere
		https://docs.python.org/3/library/io.html
		https://docs.python.org/3/library/os.path.html
"""

RECIPES_FOLDER = "recipes"

ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"

def read_file(file):
	file = open(file, 'r')
	coffee_type = file.readline()
	coffee_type = coffee_type[:-1]
	water_percent = file.readline()
	water_percent = water_percent[:-1]
	coffee_percent = file.readline()
	coffee_percent = coffee_percent[:-1]
	milk_percent = file.readline()
	milk_percent = milk_percent[:-1]

	cappuccino_capacities = []
	espresso_capacities = []
	americano_capacities = []

	if coffee_type == CAPPUCCINO:
		cappuccino_capacities = [water_percent.split("=",1)[1], coffee_percent.split("=",1)[1], milk_percent.split("=",1)[1]]
	elif coffee_type == ESPRESSO:
		espresso_capacities = [water_percent.split("=",1)[1], coffee_percent.split("=",1)[1], milk_percent.split("=",1)[1]]
	elif coffee_type == AMERICANO:
		americano_capacities = [water_percent.split("=",1)[1], coffee_percent.split("=",1)[1], milk_percent.split("=",1)[1]]

	return cappuccino_capacities, americano_capacities, espresso_capacities

