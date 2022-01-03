package tema;

public class MyRunnable implements Runnable {

    private int thread_id;

    MyRunnable(int thread_id) {
        this.thread_id = thread_id;
    }

    @Override
    public void run() {
        System.out.println("Hello world from "
                + Integer.toString(thread_id) + " thread!");
    }
}
