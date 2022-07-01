#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int _rand_init = 0;
void shuffle(int* arr, int len) {
    if (_rand_init == 0) {
        srand((unsigned int) time(NULL));
        _rand_init = 1;
    }
    for (int i = 0; i < len; i++) {
        int to = rand() % len;
        printf("%d\n", to);
        int a = arr[to];
        int b = arr[i];
        arr[i] = a;
        arr[to] = b;
    }
}


int run(int* boxes, int len) {
    shuffle(boxes, len);
    for (int n = 0; n < len; n++) {
        int b = boxes[n];
        int attempts = 0;
        while (b != n && attempts < len / 2 - 1) {
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
    int* boxes = (int*) malloc(sizeof(int) * p);
    for (int i = 0; i < p; i++) {
        boxes[i] = i;
    }
    if (!boxes) {
        fprintf(stderr, "MEM BORK: %s\n", strerror(errno));
        return -1;
    }
    for (int i = 0; i < 10000; i++) {
        int live = run(boxes, p);
        live_sum += live;
        iters += 1;
        if (!(iters % 1000)) {
            printf("%lf %d %d\n", (double) live_sum / iters, live_sum, iters);
        }
    }
    free(boxes);
    return 0;
}
