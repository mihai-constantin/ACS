"""
This module represents the Consumer.

Computer Systems Architecture Course
Assignment 1
March 2020
"""

from threading import Thread
from time import sleep

class Consumer(Thread):
    """
    Class that represents a consumer.
    """

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """

        Thread.__init__(self, **kwargs)
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time
        self.name = kwargs["name"]
        self.cart_id = -1

    def run(self):
        for current_cart in self.carts:
            self.cart_id = self.marketplace.new_cart(self.name)

            for current_order in current_cart:
                product_type = current_order["type"]
                product = current_order["product"]
                quantity = current_order["quantity"]

                if product_type == "add":
                    while quantity > 0:
                        while True:
                            ret = self.marketplace.add_to_cart(self.cart_id, product)
                            if ret:
                                break
                            sleep(self.retry_wait_time)
                        quantity -= 1
                else:
                    while quantity > 0:
                        self.marketplace.remove_from_cart(self.cart_id, product)
                        quantity -= 1

            self.marketplace.place_order(self.cart_id)
