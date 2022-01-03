class Util:
	x = 2                    # camp static

	@staticmethod            # metoda statica
	def do_stuff():
		print ("stuff")

	def do_otherstuff():     # alta varianta de a declara o metoda statica
		print ("other stuff")
	do_otherstuff = staticmethod(do_otherstuff)

print (Util.x)
Util.do_stuff()
Util.do_otherstuff()