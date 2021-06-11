import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        double n;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextDouble();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double x) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", x);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double getResult() {
            // TODO: Calculeaza sqrt(n) cu o precizie de 10^-3.
            // Precizie de 10^(-x) inseamna |valoarea_ta - valoarea_reala| < 10^(-x).

            int st = 0;
            int dr = (int) n;
            double res = 0.0;

            while(st <= dr) {
                int m = (st + dr) / 2;
                if (m * m == n) {
                    res = m;
                    break;
                }
                if (m * m < n) {
                    res = m;
                    st = m + 1;
                } else {
                    dr = m - 1;
                }
            }

            double increment = 0.1;
            int precision = 3;
            for (int i = 0; i < precision; i++) {
                while(res * res <= n) {
                    res += increment;
                }
                res -= increment;
                increment /= 10;
            }
            return res;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
