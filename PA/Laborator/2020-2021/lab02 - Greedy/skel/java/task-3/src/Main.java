import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class Main {
    static class Homework {
        public int deadline;
        public int score;

        public Homework() {
            deadline = 0;
            score = 0;
        }
    }

    static class Task {
        public final static String INPUT_FILE = "in";
        public final static String OUTPUT_FILE = "out";

        int n;
        Homework[] hws;

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new File(INPUT_FILE));
                n = sc.nextInt();
                hws = new Homework[n];
                for (int i = 0; i < n; i++) {
                    hws[i] = new Homework();
                    hws[i].deadline = sc.nextInt();
                    hws[i].score = sc.nextInt();
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
            // TODO: Aflati punctajul maxim pe care il puteti obtine planificand optim temele.
            Arrays.sort(hws, new Comparator<Homework>() {
                @Override
                public int compare(Homework hw1, Homework hw2) {
                    if (hw1.deadline == hw2.deadline) {
                        return (hw1.score < hw2.score) ? -1 : 1;
                    }
                    return (hw1.deadline < hw2.deadline) ? -1 : 1;
                }
            });

            int score = hws[hws.length - 1].score;
            hws[hws.length - 1].score = -1;
            for (int week = hws[hws.length - 1].deadline - 1; week > 0; week--) {
                int currentScore = 0;
                int pos = -1;
                for (int i = hws.length - 2; i >= 0; i--) {
                    if (hws[i].deadline < week) {
                        break;
                    }
                    if (hws[i].score != -1 && currentScore < hws[i].score) {
                        currentScore = hws[i].score;
                        pos = i;
                    }
                }
                if (currentScore != 0) {
                    score += currentScore;
                    hws[pos].score = -1;
                }
            }
            System.out.println("score: " + score);
            return score;
        }
    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
