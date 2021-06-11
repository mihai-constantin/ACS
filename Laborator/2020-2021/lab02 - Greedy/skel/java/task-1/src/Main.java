import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Main {
    static class Obj {
        public int weight;
        public int price;

        public Obj() {
            weight = 0;
            price = 0;
        }
    };

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n, w;
        Obj[] objs;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                w = sc.nextInt();
                objs = new Obj[n];
                for (int i = 0; i < n; i++) {
                    objs[i] = new Obj();
                    objs[i].weight = sc.nextInt();
                    objs[i].price = sc.nextInt();
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(double result) {
            try {
                PrintWriter pw = new PrintWriter(new File(OUTPUT_FILE));
                pw.printf("%.4f\n", result);
                pw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private double getResult() {
            // TODO: Aflati profitul maxim care se poate obtine cu obiectele date.

            // sortare descrescatoare dupa price/weight
            Arrays.sort(objs, new Comparator<Obj>() {
                @Override
                public int compare(Obj obj1, Obj obj2) {
                    return ((double)obj1.price / obj1.weight < (double)obj2.price / obj2.weight) ? 1 : -1;
                }
            });

            double profit = 0.0;
            for (Obj obj : objs) {
                if(obj.weight <= w) {
                    profit += obj.price;
                    w -= obj.weight;
                } else {
                    profit += (double)obj.price / obj.weight * w;
                    w = 0;
                    break;
                }
            }
            return profit;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
