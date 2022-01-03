from threading import Thread, Lock, Semaphore
import sys

class MyThread(Thread):

	def __init__(self, thread_id, forks, semaphore):
		Thread.__init__(self)
		self.thread_id = thread_id
		self.forks = forks
		self.semaphore = semaphore

	def run(self):

		self.semaphore.acquire()

		self.forks[self.thread_id].acquire()
		self.forks[(self.thread_id + 1) % N_PHILOSOPHERS].acquire()
		
		print("Hello, I'm Thread-" + str(self.thread_id) + " and I'm eating! ")
		
		self.forks[self.thread_id].release()
		self.forks[(self.thread_id + 1) % N_PHILOSOPHERS].release()

		self.semaphore.release()

if __name__ == '__main__':

	if len(sys.argv) != 2:
		print("Usage: " + sys.argv[0] + " num_philosophers")
		sys.exit()

	N_PHILOSOPHERS = int(sys.argv[1])

	semaphore = Semaphore(value = N_PHILOSOPHERS - 1)

	forks = []

	for i in range(N_PHILOSOPHERS):
		fork = Lock()
		forks.append(fork)

	philosophers = []

	for i in range(N_PHILOSOPHERS):
		thread = MyThread(i, forks, semaphore)
		thread.start()
		philosophers.append(thread)

	for i in range(N_PHILOSOPHERS):
		philosophers[i].join()
