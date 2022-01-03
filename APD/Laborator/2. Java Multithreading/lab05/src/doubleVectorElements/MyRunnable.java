package doubleVectorElements;

public class MyRunnable implements Runnable {

    int thread_id;
    int start;
    int end;
    int v[];

    MyRunnable(int thread_id, int v[]) {
        this.thread_id = thread_id;
        this.start = this.thread_id * (int)(Math.ceil((double)Main.N / Main.P));
        this.end = Math.min(Main.N,(this.thread_id + 1) * (int)(Math.ceil((double)Main.N / Main.P)));
        this.v = v;
    }

    @Override
    public void run() {
        for(int i = start; i < end; i++) {
            this.v[i] = this.v[i] * 2;
        }
    }
}
