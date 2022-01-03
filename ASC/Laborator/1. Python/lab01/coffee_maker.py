"""
A command-line controlled coffee maker.
"""

import sys
import io

from load_recipes import read_file

"""
Implement the coffee maker's commands. Interact with the user via stdin and print to stdout.

Requirements:
    - use functions
    - use __main__ code block
    - access and modify dicts and/or lists
    - use at least once some string formatting (e.g. functions such as strip(), lower(),
    format()) and types of printing (e.g. "%s %s" % tuple(["a", "b"]) prints "a b"
    - BONUS: read the coffee recipes from a file, put the file-handling code in another module
    and import it (see the recipes/ folder)

There's a section in the lab with syntax and examples for each requirement.

Feel free to define more commands, other coffee types, more resources if you'd like and have time.
"""

"""
Tips:
*  Start by showing a message to the user to enter a command, remove our initial messages
*  Keep types of available coffees in a data structure such as a list or dict
e.g. a dict with coffee name as a key and another dict with resource mappings (resource:percent)
as value
"""

# Commands
EXIT = "exit"
LIST_COFFEES = "list"
MAKE_COFFEE = "make"  #!!! when making coffee you must first check that you have enough resources!
HELP = "help"
REFILL = "refill"
RESOURCE_STATUS = "status"
commands = [EXIT, LIST_COFFEES, MAKE_COFFEE, REFILL, RESOURCE_STATUS, HELP]

# Coffee examples
ESPRESSO = "espresso"
AMERICANO = "americano"
CAPPUCCINO = "cappuccino"
coffee_examples = [ESPRESSO, AMERICANO, CAPPUCCINO]

# Resources examples
WATER = "water"
COFFEE = "coffee"
MILK = "milk"

# Coffee maker's resources - the values represent the fill percents
RESOURCES = {WATER: 100, COFFEE: 100, MILK: 100}

"""
Example result/interactions:

I'm a smart coffee maker
Enter command:
list
americano, cappuccino, espresso
Enter command:
status
water: 100%
coffee: 100%
milk: 100%
Enter command:
make
Which coffee?
espresso
Here's your espresso!
Enter command:
refill
Which resource? Type 'all' for refilling everything
water
water: 100%
coffee: 90%
milk: 100%
Enter command:
exit
"""

def display_coffee_examples():
	for i in range(len(coffee_examples)):
		if i == len(coffee_examples) - 1:
			print(coffee_examples[i])
		else:
			print(coffee_examples[i] + ", ", end = " ")

def resource_status():
	for x, y in RESOURCES.items():
		print(str(x) + ": " + str(y) + "%")

def verify(coffee_type):
	if coffee_type == ESPRESSO:
		if RESOURCES[WATER] < int(espresso_capacities[0]) or RESOURCES[COFFEE] < int(espresso_capacities[1]) or RESOURCES[MILK] < int(espresso_capacities[2]):
			return 0;
	elif coffee_type == CAPPUCCINO:
		if RESOURCES[WATER] < int(cappuccino_capacities[0]) or RESOURCES[COFFEE] < int(cappuccino_capacities[1]) or RESOURCES[MILK] < int(cappuccino_capacities[2]):
			return 0;
	elif coffee_type == AMERICANO:
		if RESOURCES[WATER] < int(americano_capacities[0]) or RESOURCES[COFFEE] < int(americano_capacities[1]) or RESOURCES[MILK] < int(americano_capacities[2]):
			return 0;

	return 1;

def make_coffee():
	print("Which coffee?")
	coffee_type = sys.stdin.readline()
	coffee_type = coffee_type[:-1]

	if coffee_type == ESPRESSO:
		if verify(ESPRESSO) == 1:
			RESOURCES[WATER] = RESOURCES[WATER] - int(espresso_capacities[0])
			RESOURCES[COFFEE] = RESOURCES[COFFEE] - int(espresso_capacities[1])
			RESOURCES[MILK] = RESOURCES[MILK] - int(espresso_capacities[2])
			print("Here's your " + ESPRESSO + "!")
		else:
			print("No more resources! Please refill!")
	elif coffee_type == CAPPUCCINO:
		if verify(CAPPUCCINO) == 1:
			RESOURCES[WATER] = RESOURCES[WATER] - int(cappuccino_capacities[0])
			RESOURCES[COFFEE] = RESOURCES[COFFEE] - int(cappuccino_capacities[1])
			RESOURCES[MILK] = RESOURCES[MILK] - int(cappuccino_capacities[2])
			print("Here's your " + CAPPUCCINO + "!")
		else:
			print("No more resources! Please refill!")
	else:
		if verify(AMERICANO) == 1:
			RESOURCES[WATER] = RESOURCES[WATER] - int(americano_capacities[0])
			RESOURCES[COFFEE] = RESOURCES[COFFEE] - int(americano_capacities[1])
			RESOURCES[MILK] = RESOURCES[MILK] - int(americano_capacities[2])
			print("Here's your " + AMERICANO + "!")
		else:
			print("No more resources! Please refill!")

def refill():
	print("Which resource?")
	resource_type = sys.stdin.readline()
	resource_type = resource_type[:-1]

	if resource_type == 'all':
		RESOURCES[WATER] = 100
		RESOURCES[COFFEE] = 100
		RESOURCES[MILK] = 100
	elif resource_type == 'water':
		RESOURCES[WATER] = 100
	elif resource_type == 'coffee':
		RESOURCES[COFFEE] = 100
	elif resource_type == 'milk':
		RESOURCES[MILK] = 100 

def help():
	print("list - print coffee types")
	print("make - prepare coffee")
	print("refill - refill water/coffee/milk/all")
	print("status - display water/coffee/milk percents")
	print("exit - close program")

if __name__ == "__main__":

	print("I'm a smart coffee maker")

	# read from files

	## americano.txt
	file = 'recipes/americano.txt'
	a, americano_capacities, b = read_file(file)
	## cappuccino.txt
	file = 'recipes/cappuccino.txt'
	cappuccino_capacities, a, b = read_file(file)
	## espresso.txt
	file = 'recipes/espresso.txt'
	a, b, espresso_capacities = read_file(file)

	print("******************")
	print(americano_capacities)
	print(cappuccino_capacities)
	print(espresso_capacities)
	print("******************")

	userinput = 'dummy command'
	while userinput != EXIT:
		print("Enter command:")

		userinput = sys.stdin.readline()
		userinput = userinput[:-1]

		if userinput == LIST_COFFEES:
			display_coffee_examples()

		if userinput == MAKE_COFFEE:
			make_coffee()

		if userinput == HELP:
			help()

		if userinput == REFILL:
			refill()

		if userinput == RESOURCE_STATUS:
			resource_status()

	print("Au revoir.")

