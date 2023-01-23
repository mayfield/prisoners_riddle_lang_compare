#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


void shuffle(size_t* arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        size_t to = rand() % len;
        size_t a = arr[to];
        size_t b = arr[i];
        arr[i] = a;
        arr[to] = b;
    }
}


int run(size_t* boxes, size_t len, size_t max_attempts) {
    shuffle(boxes, len);
    for (size_t n = 0; n < len; n++) {
        size_t b = boxes[n];
        int attempts = 0;
        while (b != n && attempts < max_attempts) {
            b = boxes[b];
            attempts += 1;
        }
        if (b != n) {
            return 0;
        }
    }
    return 1;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Prisoner count arg required\n");
        return -1;
    }
    int p = (int) strtol(argv[1], NULL, 0);
    if (p == -1) {
        fprintf(stderr, "Value is not a number: %s\n", strerror(errno));
        return -1;
    }
    int live_sum = 0;
    int iters = 0;
    size_t* boxes = (size_t*) malloc(sizeof(size_t) * p);
    for (size_t i = 0; i < p; i++) {
        boxes[i] = i;
    }
    if (!boxes) {
        fprintf(stderr, "MEM BORK: %s\n", strerror(errno));
        return -1;
    }
    srand((unsigned int) time(NULL));
    size_t max_attempts = p / 2 - 1;
    for (int i = 0; i < 10000; i++) {
        int live = run(boxes, p, max_attempts);
        live_sum += live;
        iters += 1;
        if (!(iters % 1000)) {
            printf("%lf %d %d\n", (double) live_sum / iters, live_sum, iters);
        }
    }
    free(boxes);
    return 0;
}
