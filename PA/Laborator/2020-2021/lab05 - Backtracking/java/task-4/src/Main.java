import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, k;
        char[] caractere;
        int[] freq;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                k = sc.nextInt();
                String s = sc.next().trim();
                s = " " + s;
                caractere = s.toCharArray();
                freq = new int[n + 1];
                for (int i = 1; i <= n; i++) {
                    freq[i] = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Character>> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.size());
                for (ArrayList<Character> arr : result) {
                    for (int i = 0; i < arr.size(); i++) {
                        pw.printf("%c", arr.get(i));
                    }
                    pw.printf("\n");
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private boolean validation(ArrayList<Character> solution, int step, int idx) {
            int nr = 0;
            while(step >= 0 && solution.get(step) == caractere[idx]) {
                step--;
                nr++;
            }
            if (nr >= k ) {
                return false;
            }
            return true;
        }

        private void bkt(int step, int stop,  ArrayList<Character> solution, ArrayList<ArrayList<Character>> all) {
             if (step == stop) {
                all.add(new ArrayList<Character>(solution));
                return;
            }

            for (int i = 1; i <= n; i++) {
                if (freq[i] > 0 && validation(solution, step - 1, i)) {
                    solution.add(step, caractere[i]);
                    freq[i]--;
                    bkt(step + 1, stop, solution, all);
                    solution.remove(step);
                    freq[i]++;
                }
            }
        }

        private ArrayList<ArrayList<Character>> getResult() {
            ArrayList<ArrayList<Character>> all = new ArrayList<>();

            // TODO: Construiti toate sirurile cu caracterele in stringul
            // caractere (indexat de la 1 la n), si frecventele in vectorul freq
            // (indexat de la 1 la n), stiind ca nu pot fi mai mult de K
            // aparitii consecutive ale aceluiasi caracter.
            //
            // Pentru a adauga un nou sir:
            //   ArrayList<Character> sir;
            //   all.add(sir);
            //

            int length = 0;
            for (int i = 1; i <= n; i++) {
                length += freq[i];
            }
            ArrayList<Character> solution = new ArrayList<>();
            
            bkt(0, length, solution, all);

            return all;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
