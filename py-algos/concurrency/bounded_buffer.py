# Threading Libraries
from threading import Thread, Semaphore, Lock, Event
from concurrent.futures import ThreadPoolExecutor

# Data structures
from collections import deque
from queue import Queue, PriorityQueue

class Buffer:
    '''
    FIFO Data Buffer that can support concurrent get/put operations
    to add and retrieve data.
    '''
    def __init__(self, max_size=0):
        self.data = deque()
        self.max_size = max_size

    def get(self):
        pass

    def put(self, val):
        pass


def producer():
    pass

def consumer():
    pass


if __name__ == "__main__":
    pass