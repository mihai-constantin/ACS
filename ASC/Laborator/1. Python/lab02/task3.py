"""
Coffee Factory: A multiple producer - multiple consumer approach

Generate a base class Coffee which knows only the coffee name
Create the Espresso, Americano and Cappuccino classes which inherit the base class knowing that
each coffee type has a predetermined size.
Each of these classes have a get message method

Create 3 additional classes as following:
    * Distributor - A shared space where the producers puts coffees and the consumers takes them
    * CoffeeFactory - An infinite loop, which always sends coffees to the distributor
    * User - Another infinite loop, which always takes coffees from the distributor

The scope of this exercise is to correctly use threads, classes and synchronization objects.
The size of the coffee (ex. small, medium, large) is chosen randomly everytime.
The coffee type is chosen randomly everytime.

Example of output:

Consumer 65 consumed espresso
Factory 7 produced a nice small espresso
Consumer 87 consumed cappuccino
Factory 9 produced an italian medium cappuccino
Consumer 90 consumed americano
Consumer 84 consumed espresso
Factory 8 produced a strong medium americano
Consumer 135 consumed cappuccino
Consumer 94 consumed americano
"""

from threading import Thread, Lock, Semaphore
import random as rand
import sys

SIZES = ["small", "medium", "large"]
ATTRIBUTE = ["nice", "italian", "strong"]

class Coffee:
    """ Base class """
    def __init__(self):
        pass

    def get_name(self):
        """ Returns the coffee name """
        raise NotImplementedError

    def get_size(self):
        """ Returns the coffee size """
        raise NotImplementedError

class Espresso(Coffee):
    def __init__(self, size, attribute):
        self.size = size
        self.attribute = attribute

    def get_name(self):
        return "espresso"

    def get_size(self):
        return self.size

    def get_attribute(self):
        return self.attribute

    def get_message(self):
        return self.get_attribute() + " " + self.size + " " + self.get_name()

class Americano(Coffee):
    def __init__(self, size, attribute):
        self.size = size
        self.attribute = attribute

    def get_name(self):
        return "americano"

    def get_size(self):
        return self.size

    def get_attribute(self):
        return self.attribute

    def get_message(self):
        return self.get_attribute() + " " + self.size + " " + self.get_name()

class Cappuccino(Coffee):
    def __init__(self, size, attribute):
        self.size = size
        self.attribute = attribute

    def get_name(self):
        return "cappuccino"

    def get_size(self):
        return self.size

    def get_attribute(self):
        return self.attribute

    def get_message(self):
        return self.get_attribute() + " " + self.size + " " + self.get_name()

# shared resources
class Distributor:
    def __init__(self, capacity):
        self.capacity = capacity
        self.buf = [None] * self.capacity
        self.first = 0
        self.last = 0
        self.empty = Semaphore(value = self.capacity)
        self.full = Semaphore(value = 0)
        self.mutexP = Lock()
        self.mutexC = Lock()

    def put(self, elem):
        self.empty.acquire()

        with self.mutexP:
            self.buf[self.last] = elem
            self.last = (self.last + 1) % self.capacity

        self.full.release()

    def get(self):
        self.full.acquire()

        elem = None

        with self.mutexC:
            elem = self.buf[self.first]
            self.first = (self.first + 1) % self.capacity

        self.empty.release()

        return elem

# producer
class CoffeeFactory(Thread):
    # infinite loop
    def __init__(self, thread_id, buf, coffee_types):
        Thread.__init__(self)
        self.thread_id = thread_id
        self.buf = buf;
        self.coffee_types = coffee_types

    def run(self):
        while True:
            elem = self.coffee_types[rand.randint(0, 2)](SIZES[rand.randint(0, 2)], ATTRIBUTE[rand.randint(0, 2)])
            print("Factory " + str(self.thread_id) + " produce a " + elem.get_message())
            self.buf.put(elem)

# consumer
class User(Thread):
    # infinite loop
    def __init__(self, thread_id, buf):
        Thread.__init__(self)
        self.thread_id = thread_id
        self.buf = buf

    def run(self):
        while True:
            elem = self.buf.get()
            print("Consumer " + str(self.thread_id) + " consumed a " + elem.get_message())

if __name__ == '__main__':

    if len(sys.argv) != 4:
        print("Usage: " + sys.argv[0] + " N_PRODUCERS N_CONSUMERS BUFFER_CAPACITY")
        sys.exit()

    rand.seed() # seed-ul este current system time pentru generatorul de nr random

    coffee_types = [Espresso, Americano, Cappuccino]

    thread_list = []

    N_PRODUCERS = int(sys.argv[1])
    N_CONSUMERS = int(sys.argv[2])

    buf = Distributor(int(sys.argv[3]) - 1)

    for i in range(N_PRODUCERS):
        thread = CoffeeFactory(i, buf, coffee_types)
        thread.start()
        thread_list.append(thread)

    for i in range(N_CONSUMERS):
        thread = User(i, buf)
        thread.start()
        thread_list.append(thread)

    for i in range(N_PRODUCERS + N_CONSUMERS):
        thread_list[i].join()

