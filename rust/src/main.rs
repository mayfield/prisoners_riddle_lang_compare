#![allow(unused)]

use std::env;
use rand::SeedableRng;
use rand::RngCore;
use rand::rngs::StdRng;

static mut RNG: Option<StdRng> = None;


unsafe fn shuffle(arr: &mut Vec<u32>) {
    if RNG.is_none() {
        RNG = Some(StdRng::from_entropy());
    }
    let mut rng = RNG.as_mut().unwrap();
    let len = arr.len();
    for i in 0..len {
        let to: usize = rng.next_u64() as usize % len;
        let a = arr[to];
        let b = arr[i];
        arr[to] = b;
        arr[i] = a;
    }
}


fn run(boxes: &mut Vec<u32>) -> bool {
    unsafe {
        shuffle(boxes);
    }
    let p: u32 = boxes.len() as u32;
    let max_attempts = p / 2 -1;
    for n in 0..p {
        let mut b = boxes[n as usize];
        let mut attempts = 0;
        while b != n && attempts < max_attempts {
            b = boxes[b as usize];
            attempts += 1;
        }
        if b != n {
            return false;
        }
    }
    return true;
}


fn main() {
    let p: usize = env::args().nth(1)
        .expect("Missing prisoner size").parse()
        .expect("Prisoner size must be positive number");

    let mut boxes: Vec<u32> = (0..p as u32).collect();
    let mut live_sum: u64 = 0;
    let mut iters: u64 = 0;
    for i in 0..10000 {
        let live = run(&mut boxes);
        live_sum = live_sum + live as u64;
        iters += 1;
        if iters % 1000 == 0 {
            let ratio: f64 = live_sum as f64 / iters as f64;
            println!("{ratio}, {live_sum}, {iters}");
        }
    }
}
