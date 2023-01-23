
const print = console.debug.bind(console);
const p = Number(process.argv[2]);
const maxAttempts = p / 2 - 1;
const boxes = new Uint32Array(p);
for (let i = 0; i < p; i++) {
    boxes[i] = i;
}


class FastRandom {
    constructor() {
        this._seed = (Math.random() * 0x7fffffff) >>> 0;
    }

    next() {
        return this._seed = this._seed * 16807 % 0x7fffffff;
        //return this._seed = (this._seed * 16807) & 0x7fffffff;
    }

    nextFloat() {
        return (this.next() - 1) / 0x7fffffff
    }
}

const fastRandom = new FastRandom();

let _seed = (Math.random() * 0x7fffffff) >>> 0;
function next() {
    _seed = (_seed * 16807) >>> 0;
    //return this._seed = (this._seed * 16807) & 0x7fffffff;
    return _seed;
}


function shuffle(arr) {
    for (let i = 0; i < arr.length; i++) {
        //const to = fastRandom.next() % arr.length;
        const to = next() % arr.length;
        //const to = (Math.random() * arr.length) >>> 0;
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
            return 0;
        }
    }
    return 1;
}


let liveSum = 0;
let iters = 0;
for (let i = 0; i < 10000; i++) {
    const live = run();
    liveSum += live;
    iters += 1;
    if (!(iters % 1000)) {
        print(liveSum / iters, liveSum, iters);
    }
}
