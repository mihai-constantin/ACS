class Student:
	"""  O clasa care reprezinta un student. Comentariile docstring se pun dupa declaratie :) """

	def __init__(self, name, grade=5):   # constructor cu parametru default; echivalent cu mai multi constructori overloaded
		self.name = name                 # campurile clasei pot fi declarate oriunde!
		self.change_grade(grade)         # apelul unei metode a clasei

	def change_grade(self, grade):       # primul parametru este intotdeauna 'self'
		self.grade = grade               # adauga nou camp clasei


x = Student("Alice")
y = Student("Bob", 10)
x.change_grade(8)

print(x.name + " " + str(x.grade))
print(y.name + " " + str(y.grade))