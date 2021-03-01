package queens;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class Main {

    static int N = 8;
    static ExecutorService tpe = Executors.newFixedThreadPool(4);

    public static void printQueens(int[] queens) {
        for(int i = 0; i < queens.length; i++) {
            for(int j = 0; j < queens.length; j++) {
                if(queens[i] == j) {
                    System.out.print("X");
                }
                else {
                    System.out.print("-");
                }
            }
            System.out.println();
        }

        System.out.println();
    }

    public static boolean verifyQueens(int[] queens, int step) {
        // same row
        for (int i = 0; i < step; i++) {
            for (int j = 0; j < step; j++) {
                if (i != j && queens[i] == queens[j]) {
                    return false;
                }
            }
        }

        // same diags
        int sum = 0;
        /*
         * for (int i = 0; i < step - 1; i++) { if (queens[i] == queens[i + 1] + 1 ||
         * queens[i] == queens[i + 1] - 1) { return false; } }
         */

        for (int i = 0; i < step; i++) {
            for (int j = 0; j < step; j++) {
                if (i != j && i + queens[i] == j + queens[j]) {
                    return false;
                }
            }
        }

        for (int i = 0; i < step; i++) {
            for (int j = 0; j < step; j++) {
                if (i != j && queens[i] - i == queens[j] - j) {
                    return false;
                }
            }
        }

        return true;
    }

    public static void main(String[] args) {

        int[] queens = new int[N];
        tpe.submit(new Task(queens, 0));
    }
}

class Task implements Runnable {

    int[] queens;
    int step;

    public Task(int[] queens, int step) {
        this.queens = queens;
        this.step = step;
    }

    @Override
    public void run() {

        if(step == Main.N) {

            if(Main.verifyQueens(queens, step)) {
                Main.printQueens(queens);

                Main.tpe.shutdown();
                try {
                    if (!Main.tpe.awaitTermination(1, TimeUnit.SECONDS)) {
                        Main.tpe.shutdownNow();
                    }
                } catch (InterruptedException e) {
                    // e.printStackTrace();
                }

            }
        }

        for(int i = 0; i < Main.N; i++) {
            int[] newQueens = queens.clone();
            newQueens[step] = i;
            Main.tpe.submit(new Task(newQueens, step + 1));
        }
    }
}
