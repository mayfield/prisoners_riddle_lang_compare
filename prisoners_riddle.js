
const print = console.debug.bind(console);
const p = Number(process.argv[2]);
const maxAttempts = p / 2 - 1;
const boxes = Array.from(new Array(p)).map((_, i) => i);

function shuffle(arr) {
    for (let i = 0; i < arr.length; i++) {
        const to = Math.trunc(Math.random() * arr.length);
        [arr[to], arr[i]] = [arr[i], arr[to]];
    }
}


function run() {
    shuffle(boxes);
    for (let n = 0; n < p; n++) {
        let b = boxes[n];
        let attempts = 0;
        while (b !== n && attempts < maxAttempts) {
            b = boxes[b];
            attempts += 1;
        }
        if (b !== n) {
            return false;
        }
    }
    return true;
}


let liveSum = 0;
let iters = 0;
for (let i = 0; i < 10000; i++) {
    const live = run();
    liveSum += Number(live);
    iters += 1;
    if (!(iters % 1000)) {
        print(liveSum / iters, liveSum, iters);
    }
}
