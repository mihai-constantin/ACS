package ReadAndSort;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

class ReaderThread extends Thread {
    String fileName;

    public ReaderThread(String fileName) {
        this.fileName = fileName;
    }

    public void run() {
        try {
            BufferedReader br = new BufferedReader(new FileReader(this.fileName));
            String line;
            while ((line = br.readLine()) != null) {

                // TODO add in list
                Main.list.add(Integer.valueOf(line));
            }
            br.close();

        } catch (IOException e) {

        }

        // TODO semaphore stuff
        Main.semaphore.release();
    }

}

class SortThread extends Thread {
    public void run() {
        try {

            // TODO semaphore stuff
            Main.semaphore.acquire();

        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        // TODO sorting list
        Collections.sort(Main.list);

    }

}

public class Main {
    // TODO semaphore init
    static Semaphore semaphore = new Semaphore(-2);

    // TODO list init
    static List<Integer> list = Collections.synchronizedList(new ArrayList<>());

    public static void main(String[] args) {
        Thread threads[] = new Thread[4];

        threads[0] = new ReaderThread("elemente1.txt");
        threads[1] = new ReaderThread("elemente2.txt");
        threads[2] = new ReaderThread("elemente3.txt");
        threads[3] = new SortThread();

        for (int i = 0; i < 4; i++) {
            threads[i].start();
        }

        for (int i = 0; i < 4; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }

        System.out.print(list);
    }

}
