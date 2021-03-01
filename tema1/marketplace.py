"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2020
"""

from threading import Lock

class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """
    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        self.queue_size_per_producer = queue_size_per_producer

        # init prod_id
        self.prod_id = 0

        # init products dictionary
        self.products = {}

        # init cart_id
        self.cart_id = 0

        # init carts dictionary
        self.carts = {}

        # init consumer_names dictionary
        self.consumer_names = {}

        # init marketplace
        self.marketplace = []

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """
        lock = Lock()
        with lock:
            self.prod_id += 1
            # init list for self.prod_id
            self.products[self.prod_id] = []
            return self.prod_id

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """
        if len(self.products[producer_id]) < self.queue_size_per_producer:
            self.products[producer_id].append(product)
            self.marketplace.append((product, producer_id))
            return True

        return False

    def new_cart(self, consumer_name):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id
        """
        lock = Lock()
        with lock:
            self.cart_id += 1
            self.consumer_names[self.cart_id] = consumer_name

            # init list for self.cart_id
            self.carts[self.cart_id] = []
            return self.cart_id

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """
        for (prod, prod_id) in self.marketplace:
            if prod == product and product in self.products[prod_id]:
                self.carts[cart_id].append((product, prod_id))
                self.products[prod_id].remove(product)
                self.marketplace.remove((prod, prod_id))
                return True

        return False

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """
        # print(str(cart_id) + ": " + str(self.carts[cart_id]))
        # print(product)
        # print(self.marketplace)

        for (prod, _producer_id) in self.carts[cart_id]:
            if prod == product:
                self.carts[cart_id].remove((product, _producer_id))
                self.products[_producer_id].append(product)
                self.marketplace.append((prod, _producer_id))
                return

    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        for (product, _producer_id) in self.carts[cart_id]:
            print(str(self.consumer_names[cart_id]) + " bought " + str(product))

        return [i[0] for i in self.carts[cart_id]]
