import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        int[] v;
        int x;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                v = new int[n];
                for (int i = 0; i < n; i++) {
                    v[i] = sc.nextInt();
                }
                x = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(int count) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", count);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private int findFirst() {
            // TODO: Cautati prima pozitie din v pe care se afla valoarea x.
            // In cazul in care nu exista in sir, returnati -1.
            int res = -1;
            int left = 0;
            int right = n - 1;
            while(left <= right) {
                int m = (left + right) / 2;
                if (v[m] >= x) {
                    res = m;
                    right = m - 1;
                } else {
                    left = m + 1;
                }
            }
            return res;
        }

        private int findLast() {
            // TODO: Cautati ultima pozitie din v pe care se afla valoarea x.
            // In cazul in care nu exista in sir, returnati -1.
            int res = -1;

            int left = 0;
            int right = n - 1;

            while(left <= right) {
                int m = (left + right) / 2;
                if (v[m] <= x) {
                    res = m;
                    left = m + 1;
                } else {
                    right = m - 1;
                }
            }
            return res;
        }

        private int getResult() {
            // TODO: Calculati numarul de aparitii a numarului x in vectorul v.
            if (findFirst() == -1 || findLast() == -1) {
                return 0;
            }
            return findLast() - findFirst() + 1;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
