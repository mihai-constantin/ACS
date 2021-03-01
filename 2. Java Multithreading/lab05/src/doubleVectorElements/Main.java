package doubleVectorElements;

/**
 * @author cristian.chilipirea
 */
public class Main {

    public static int N = 100000013; // number of elements
    public static int P = 4; // number of threads

    public static void main(String[] args) {
        int v[] = new int[N];
        for (int i = 0; i < N; i++)
            v[i] = i;

        Thread[] threads = new Thread[P];
        for (int i = 0; i < P; i++) {
            threads[i] = new Thread(new MyRunnable(i, v));
        }

        for (int i = 0; i < P; i++) {
            threads[i].start();
        }

        System.out.println("Hello world from main thread");

        for (int i = 0; i < P; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        for (int i = 0; i < N; i++) {
            if (v[i] != i * 2) {
                System.out.println("Wrong answer");
                System.exit(1);
            }
        }
        System.out.println("Correct");
    }

}
