package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	ArrayBlockingQueue<Integer> arrayBlockingQueue = new ArrayBlockingQueue<>(Main.N);

	void put(int value) throws InterruptedException {
//		a = value;

		arrayBlockingQueue.put(value);
	}

	int get() throws InterruptedException {
		return arrayBlockingQueue.take();
	}
}
