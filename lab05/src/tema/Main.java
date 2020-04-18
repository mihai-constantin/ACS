package tema;

public class Main {

    public static void main(String[] args) {

        int P = 4; // number of threads

        Thread[] threads = new Thread[P];
        for(int i = 0; i < P; i++) {
            threads[i] = new Thread(new MyRunnable(i));
        }

        for(int i = 0; i < P; i++) {
            threads[i].start();
        }

        System.out.println("Hello world from main thread");

        for(int i = 0; i < P; i++) {
            try {
                threads[i].join();
            }
            catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
