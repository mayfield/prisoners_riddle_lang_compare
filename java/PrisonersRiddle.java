import java.util.Random;
import java.util.ArrayList;

class ArrayRunner {

    private int[] boxesArr;
    private Random rando;

    ArrayRunner(int len) {
        this.boxesArr = new int[len];
        int liveSum = 0;
        int iters = 0;
        this.rando = new Random();
        for (int i = 0; i < len; i++) {
            this.boxesArr[i] = i;
        }
        for (int i = 0; i < 10000; i++) {
            int live = this.run();
            liveSum += live;
            iters += 1;
            if (iters % 1000 == 0) {
                System.out.printf("%f %d %d\n", (double) liveSum / iters, liveSum, iters);
            }
        }
    }

    void shuffle() {
        for (int i = 0; i < this.boxesArr.length; i++) {
            int to = this.rando.nextInt(this.boxesArr.length);
            int a = this.boxesArr[to];
            int b = this.boxesArr[i];
            this.boxesArr[i] = a;
            this.boxesArr[to] = b;
        }
    }

    int run() {
        this.shuffle();
        for (int n = 0; n < this.boxesArr.length; n++) {
            int b = this.boxesArr[n];
            int attempts = 0;
            while (b != n && attempts < this.boxesArr.length / 2 - 1) {
                b = this.boxesArr[b];
                attempts += 1;
            }
            if (b != n) {
                return 0;
            }
        }
        return 1;
    }
}


class VecRunner {

    private ArrayList<Integer> boxesVec;
    private Random rando;

    VecRunner(int len) {
        this.boxesVec = new ArrayList<Integer>();
        int liveSum = 0;
        int iters = 0;
        this.rando = new Random();
        for (int i = 0; i < len; i++) {
            this.boxesVec.add(i);
        }
        for (int i = 0; i < 10000; i++) {
            int live = this.run();
            liveSum += live;
            iters += 1;
            if (iters % 1000 == 0) {
                System.out.printf("%f %d %d\n", (double) liveSum / iters, liveSum, iters);
            }
        }
    }

    void shuffle() {
        for (int i = 0; i < this.boxesVec.size(); i++) {
            int to = this.rando.nextInt(this.boxesVec.size());
            int a = this.boxesVec.get(to);
            int b = this.boxesVec.get(i);
            this.boxesVec.set(i, a);
            this.boxesVec.set(to, b);
        }
    }

    int run() {
        this.shuffle();
        for (int n = 0; n < this.boxesVec.size(); n++) {
            int b = this.boxesVec.get(n);
            int attempts = 0;
            while (b != n && attempts < this.boxesVec.size() / 2 - 1) {
                b = this.boxesVec.get(b);
                attempts += 1;
            }
            if (b != n) {
                return 0;
            }
        }
        return 1;
    }
}

class PrisonersRiddle {
    public static void main(String args[]) {
        if (args.length < 1) {
            System.err.printf("Prisoner count arg required\n");
            System.exit(-1);
            return;
        }
        int len;
        try {
            len = Integer.parseInt(args[0]);
        } catch(NumberFormatException e) {
            System.err.printf("Invalid prisoner count arg! %s\n", e);
            System.exit(-1);
            return;
        }
        if (args.length > 1 && args[1].equals("--vector")) {
            new VecRunner(len);
        } else {
            new ArrayRunner(len);
        }
    }
}
