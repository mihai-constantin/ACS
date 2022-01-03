"""
    Basic thread handling exercise:

    Use the Thread class to create and run more than 10 threads which print their name and a random
    number they receive as argument. The number of threads must be received from the command line.

    e.g. Hello, I'm Thread-96 and I received the number 42

"""

from threading import Thread
import random as rand
import sys

class MyThread(Thread):

	def __init__(self, thread_id, nr):
		Thread.__init__(self)
		self.thread_id = thread_id
		self.nr = nr

	def run(self):
		print("Hello, I'm Thread-" + str(self.thread_id) + " and I received the number " + str(self.nr))

if __name__ == "__main__":

	if len(sys.argv) != 2:
		print("Usage: " + sys.argv[0] + " num_threads")
		sys.exit()

	numberOfThreads = sys.argv[1];

	# stocam obiectele Thread pentru a putea face join
	thread_list = []

	rand.seed() # seed-ul este current system time pentru generatorul de nr random

	# creare thread-uri
	for i in range(int(numberOfThreads)):
		thread = MyThread(i, rand.randint(0, 100))
		thread_list.append(thread)

	# pornim thread-urile
	for i in range(int(numberOfThreads)):
		thread_list[i].start()

	# join
	for i in range(int(numberOfThreads)):
		thread_list[i].join()
		
