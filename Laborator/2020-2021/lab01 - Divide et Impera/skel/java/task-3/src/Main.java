import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, x, y;

        public void solve() {
            readInput();
            writeOutput(getResult(n, x, y));
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                x = sc.nextInt();
                y = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int answer) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", answer);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int calcul(int lin, int col, int lat) {
            int r = 0;
            if (lat == 1) {
                return 1;
            }

            lat /= 2;

            // jumatatea de jos
            if (lin > lat) {
                r += 2 * lat * lat;
                lin -= lat;
            }

            // jumatatea din dreapta
            if (col > lat) {
                r += lat * lat;
                col -= lat;
            }
            return r + calcul(lin, col, lat);
        }

        private int getResult(int n, int x, int y) {
            // TODO: Calculati valoarea de pe pozitia (x, y) din matricea de dimensiune 2^n * 2^n.
            return calcul(x, y, (1 << n));
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
