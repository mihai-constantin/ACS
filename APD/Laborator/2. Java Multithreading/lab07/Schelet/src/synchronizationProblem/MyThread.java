package synchronizationProblem;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author cristian.chilipirea
 * 
 */
public class MyThread implements Runnable {
	int id;
//	static int value = 0;

	static AtomicInteger value = new AtomicInteger();

	MyThread(int id) {
		this.id = id;
	}

	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++)
//				value = value + 3;
				value.addAndGet(3);
		} else {
			for (int i = 0; i < Main.N; i++)
//				value = value + 3;

			value.addAndGet(3);
		}
	}
}
