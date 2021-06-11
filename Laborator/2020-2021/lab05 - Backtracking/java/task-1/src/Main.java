import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, k;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                k = sc.nextInt();
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(ArrayList<ArrayList<Integer>> result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%d\n", result.size());
                for (ArrayList<Integer> arr : result) {
                    for (int i = 0; i < arr.size(); i++) {
                        pw.printf("%d%c", arr.get(i), i + 1 == arr.size() ?
                                '\n' : ' ');
                    }
                }
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void bkt(int step, int stop, ArrayList<Integer> domain, ArrayList<Integer> solution,
                         Set<Integer> visited, ArrayList<ArrayList<Integer>> all) {
            if (step == stop) {
                all.add(new ArrayList<>(solution));
                return;
            }

            for (int i = 0; i < n; i++) {
                if (!visited.contains(domain.get(i))) {
                    visited.add(domain.get(i));
                    solution.add(step, domain.get(i));
                    bkt(step + 1, stop, domain, solution, visited, all);
                    solution.remove(solution.size() - 1);
                    visited.remove(domain.get(i));
                }
            }
        }

        private ArrayList<ArrayList<Integer>> getResult() {
            ArrayList<ArrayList<Integer>> all = new ArrayList<>();

            // TODO: Construiti toate aranjamentele de N luate cate K ale
            // multimii {1, ..., N}.
            //
            // Pentru a adauga un nou aranjament:
            //   ArrayList<Integer> aranjament;
            //   all.add(aranjament);
            //

            Set<Integer> visited = new HashSet<Integer>(0);
            ArrayList<Integer> solution = new ArrayList<>(k);
            ArrayList<Integer> domain = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                domain.add(i + 1);
            }

            bkt(0, k, domain, solution, visited, all);

            return all;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
