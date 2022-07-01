import sys
import random

p = int(sys.argv[1])
boxes = [i for i in range(p)]
max_attempts = p / 2 - 1


def shuffle(arr):
    l = len(arr)
    for i in range(l):
        to = int(random.random() * l)
        a = arr[i]
        b = arr[to]
        arr[to] = a
        arr[i] = b


def run():
    shuffle(boxes)
    for n in range(p):
        b = boxes[n]
        attempts = 0
        while b != n and attempts < max_attempts:
            b = boxes[b]
            attempts += 1
        if b != n:
            return 0
        n += 1
    return 1

live_sum = 0
iters = 0
for i in range(10000):
    live = run()
    live_sum += live
    iters += 1
    if not iters % 1000:
        print(live_sum / iters, live_sum, iters)
