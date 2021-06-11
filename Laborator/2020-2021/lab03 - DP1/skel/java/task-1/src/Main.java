import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, S;
        int[] v;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                S = sc.nextInt();
                v = new int[n + 1];
                for (int i = 1; i <= n; i++) {
                    v[i] = sc.nextInt();
                }
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

        private int getResult() {
            // TODO: Aflati numarul minim de monede ce poate fi folosit pentru a
            // obtine suma S. Tipurile monedelor sunt stocate in vectorul v, de
            // dimensiune n.

            int scores[] = new int[S + 1];
            Arrays.fill(scores, -1);
            scores[0] = 0;
            for (int i = 1; i <= n; i++) {
                for (int j = v[i]; j <= S; j++) {
                    if (scores[j] == -1 && scores[j - v[i]] != -1) {
                        scores[j] = 1 + scores[j - v[i]];
                    } else if (scores[j] > 1 + scores[j - v[i]]) {
                        scores[j] = 1 + scores[j - v[i]];
                    }
                }
            }
            return scores[S];
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
