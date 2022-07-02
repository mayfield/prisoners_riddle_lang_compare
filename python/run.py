import pr
import sys
import random
import array

p = int(sys.argv[1])
accel = '--accel' in sys.argv


def _shuffle(arr):
    l = len(arr)
    for i in range(l):
        to = int(random.random() * l)
        a = arr[i]
        b = arr[to]
        arr[to] = a
        arr[i] = b


max_attempts = p / 2 - 1
def _run(boxes):
    shuffle(boxes)
    for n in range(p):
        b = boxes[n]
        attempts = 0
        while b != n and attempts < max_attempts:
            b = boxes[b]
            attempts += 1
        if b != n:
            return 0
    return 1


if accel:
    shuffle = pr.shuffle
    run = pr.run
else:
    shuffle = _shuffle
    run = _run

live_sum = 0
iters = 0
#boxes = [i for i in range(p)]
boxes = array.array('I', [i for i in range(p)])
tc = boxes.typecode
for i in range(10000):
    live = run(boxes, tc)
    live_sum += live
    iters += 1
    if not iters % 1000:
        print(live_sum / iters, live_sum, iters)
