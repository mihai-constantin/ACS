package par_FloydWarshall;

public class Main {

    static int P = 4;

    public static void main(String[] args) {
        int M = 9;
        int graph[][] = { { 0, 1, M, M, M },
                { 1, 0, 1, M, M },
                { M, 1, 0, 1, 1 },
                { M, M, 1, 0, M },
                { M, M, 1, M, 0 } };

        Thread[] threads = new Thread[P];

        for(int k = 0; k < 5; k++) {

            for (int i = 0; i < P; i++) {
                threads[i] = new Thread(new MyRunnable(i, graph, k));
            }

            for (int i = 0; i < P; i++) {
                threads[i].start();
            }

            for (int i = 0; i < P; i++) {
                try {
                    threads[i].join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        System.out.println("Hello world from main thread");

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                System.out.print(graph[i][j] + " ");
            }
            System.out.println();
        }
    }
}
