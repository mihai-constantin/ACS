package multipleProducersMultipleConsumers;
/**
 * @author cristian.chilipirea
 * 
 *         DO NOT MODIFY
 */
public class Consumer implements Runnable {
	Buffer buffer;
	int id;
	static int i = 0;

	Consumer(Buffer buffer, int id) {
		this.buffer = buffer;
		this.id = id;
	}

	int getNextI() {
		int value;
		synchronized (Consumer.class) {
			value = i;
			i++;
		}
		return value;
	}

	@Override
	public void run() {
		while (true) {
			int i = getNextI();
			if (i >= Main.N_PRODUCERS * Main.N)
				break;
			synchronized (Main.results) {
				try {
					Main.results[buffer.get()]++;
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
		System.out.println("Consumer " + id + " finished Correctly");
	}
}
/* DO NOT MODIFY */