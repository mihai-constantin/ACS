package par_FloydWarshall;

public class MyRunnable implements Runnable {

    int thread_id;
    int graph[][];
    int k;
    int start;
    int end;

    MyRunnable(int thread_id, int graph[][], int k) {
        this.thread_id = thread_id;
        this.graph = graph;
        this.k = k;
        this.start = this.thread_id * (int)(Math.ceil((double)(5) / Main.P));
        this.end = Math.min(5, (this.thread_id + 1) * (int)(Math.ceil((double)(5) / Main.P)));
    }

    @Override
    public void run() {
        for (int i = start; i < end; i++) {
            for (int j = 0; j < 5; j++) {
                graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
            }
        }
    }
}
