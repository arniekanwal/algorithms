'''
The goal of this file is as an exercise to learn about concurrency/threading 
specifically in Python3 using it's native threading libraries.

Topics we'll touch include:
1) Manage threads via ThreadPoolExecutor
2) Create our own thread-safe buffer as a solution to the Producer-Consumer problem
3) Compare our custom bounded buffer vs queue.Queue()
4) Explore Python locks and semaphores
5) Learn about GIL (Global Interpreter Lock)
'''

# Threading Libraries
from threading import Thread, Semaphore, Lock
from concurrent.futures import ThreadPoolExecutor

# Data structures
from collections import deque
from queue import Queue, PriorityQueue

SENTINEL = object() # This is a POISON PILL (or terminator) to notify consumers that a producer is done

class Buffer:
    '''
    FIFO Data Buffer that can support concurrent get/put operations
    to add and retrieve data.
    '''
    def __init__(self, max_size=0):
        self.data = deque()
        self.max_size = max_size

        self.sem_full = Semaphore(0) # Initialized as 0 because buffer is initially empty (notify producers first)
        self.sem_empty = Semaphore(max_size) # Opposite behavior as full to notify consumers

        self.data_lock = Lock() # Lock to prevent race conditions when entering the critical section

    def put(self, val): # producer call
        self.sem_empty.acquire()

        self.data_lock.acquire()
        self.data.append(val)
        self.data_lock.release()

        self.sem_full.release()

    def get(self): # consumer call
        self.sem_full.acquire() 

        self.data_lock.acquire()
        msg = self.data.popleft()
        self.data_lock.release()

        self.sem_empty.release()
        return msg



def produce(self, buffer, start, end, delta):
    if end <= start:
        return

    for num in range(start, end + 1, delta):
        buffer.put(num)
    
    buffer.put(SENTINEL) # put POSION PILL into buffer to notify consumer thread

def consume(self, buffer):
    while True:
        msg = buffer.get()
        if msg is SENTINEL:
            break
        print(msg)


if __name__ == "__main__":
    print("--- Main Thread Starting ---")
    my_thread_safe_buffer = Buffer(5)

    # Test single threaded functionality of the buffer.
    print("Test single-threaded functionality of buffer")
    my_thread_safe_buffer.put(100)
    my_thread_safe_buffer.put(200)
    print(my_thread_safe_buffer.get())
    print(my_thread_safe_buffer.get())

    # utilize thread pool as context manager (synchronization handled for you automatically)
    print("--- Worker Threads Starting ---")
    
    with ThreadPoolExecutor(max_workers=4) as executor: 
        executor.submit(produce, my_thread_safe_buffer, 1, 19, 2) # print odd numbers 1 - 19
        executor.submit(produce, my_thread_safe_buffer, 2, 20, 2) # print even numbers 2 - 20

        executor.submit(consume, my_thread_safe_buffer)
        # executor.submit(worker.consume, my_thread_safe_buffer)
    
    print("--- Worker Threads Done ---")
    print("--- Main Thread Done ---")