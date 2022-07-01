import sys
import random
import dis

p = int(sys.argv[1])
boxes = [i for i in range(p)]
max_attempts = p / 2 - 1

def run():
    random.shuffle(boxes)
    for n in range(p):
        b = boxes[n]
        attempts = 0
        while b != n and attempts < max_attempts:
            b = boxes[b]
            attempts += 1
        if b != n:
            return False
    return True

live_ratio = 0
iters = 0
for i in range(10000):
    live = run()
    live_ratio += bool(live)
    iters += 1
    if not iters % 1000:
        print(live_ratio / iters, live, iters)

print(dis.dis(run))
