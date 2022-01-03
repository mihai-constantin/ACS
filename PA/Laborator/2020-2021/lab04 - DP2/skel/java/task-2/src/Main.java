import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        private final static int MOD = 1000000007;

        int n;
        char[] expr;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                String s = sc.next().trim();
                s = " " + s;
                expr = s.toCharArray();
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
            // TODO: Calculati numarul de moduri in care se pot aseza
            // parantezele astfel incat rezultatul expresiei sa fie TRUE.
            // Numarul de moduri se va calcula modulo MOD (1000000007).

            int length = expr.length;

            // T[i][j] = numarul de posibilitati de a paranteza de la i la j ai expresia sa fie evaluata la true
            long[][] T = new long[length][length];

            // F[i][j] = numarul de posibilitati de a paranteza de la i la j ai expresia sa fie evaluata la false
            long[][] F = new long[length][length];

            // cazul de baza - lungime expresie 1
            for (int i = 1; i < length; i++) {
                if (expr[i] == 'T') {
                    T[i][i] = 1L;
                } else if (expr[i] == 'F') {
                    F[i][i] = 1L;
                }
            }

            // recurenta - DP
            for (int len = 2; len < length; len++) {
                for (int i = 1; i + len - 1 < length; i++) {
                    int j = i + len - 1;
                    for (int k = i; k < j; k++) {
                        if (expr[k] == '|') {
                            T[i][j] =   (T[i][j] % MOD +
                                    (1L * (T[i][k - 1] % MOD) * (T[k + 1][j] % MOD)) % MOD +
                                    (1L * (F[i][k - 1] % MOD) * (T[k + 1][j] % MOD)) % MOD +
                                    (1L * (T[i][k - 1] % MOD) * (F[k + 1][j] % MOD)) % MOD) % MOD;
                            F[i][j] =   (F[i][j] % MOD +
                                    (1L * (F[i][k - 1] % MOD) * (F[k + 1][j] % MOD)) % MOD) % MOD;
                        } else if (expr[k] == '&') {
                            T[i][j] =   (T[i][j] % MOD +
                                    (1L * (T[i][k - 1] % MOD) * (T[k + 1][j] % MOD)) % MOD) % MOD;
                            F[i][j] =   (F[i][j] % MOD +
                                    (1L * (F[i][k - 1] % MOD) * (F[k + 1][j] % MOD)) % MOD +
                                    (1L * (F[i][k - 1] % MOD) * (T[k + 1][j] % MOD)) % MOD +
                                    (1L * (T[i][k - 1] % MOD) * (F[k + 1][j] % MOD)) % MOD) % MOD;
                        } else if (expr[k] == '^') {
                            T[i][j] =   (T[i][j] % MOD +
                                    (1L * (T[i][k - 1] % MOD) * (F[k + 1][j] % MOD)) % MOD +
                                    (1L * (F[i][k - 1] % MOD) * (T[k + 1][j] % MOD)) % MOD) % MOD;
                            F[i][j] =   (F[i][j] % MOD +
                                    (1L * (F[i][k - 1] % MOD) * (F[k + 1][j] % MOD)) % MOD +
                                    (1L * (T[i][k - 1] % MOD) * (T[k + 1][j] % MOD)) % MOD) % MOD;
                        }
                    }
                }
            }

            return (int)T[1][length - 1];
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
