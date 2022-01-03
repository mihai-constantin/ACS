package multipleProducersMultipleConsumers;
/**
 * @author cristian.chilipirea
 * 
 *         DO NOT MODIFY
 */
public class Producer implements Runnable {
	Buffer buffer;
	int id;

	Producer(Buffer buffer, int id) {
		this.buffer = buffer;
		this.id = id;
	}

	@Override
	public void run() {
		for (int i = 0; i < Main.N; i++) {
			// System.out.println(i);
			try {
				buffer.put(i);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		System.out.println("Producer " + id + " finished Correctly");
	}

}
/* DO NOT MODIFY */