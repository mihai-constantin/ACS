import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int base;
        int exponent;
        int mod;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                base = sc.nextInt();
                exponent = sc.nextInt();
                mod = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int fastPow(long base, int exponent, int mod) {
            // TODO: Calculati (base^exponent) modulo mod in O(log exponent).
            long ans = 1;
            while(exponent != 0) {
                if (exponent % 2 == 1) {
                    ans = (1L * (ans % mod) * (base % mod)) % mod;
                }
                base = (1L * (base % mod) * (base % mod)) % mod;
                exponent /= 2;
            }
            return (int)ans;
        }

        private int getResult() {
            return fastPow(base, exponent, mod);
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
