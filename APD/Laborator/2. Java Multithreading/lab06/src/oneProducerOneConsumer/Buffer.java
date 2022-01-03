package oneProducerOneConsumer;
/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	int a;
	boolean isEmpty;

	Buffer() {
		isEmpty = true;
	}

	synchronized void put(int value) throws InterruptedException {
		if(!isEmpty) {
			wait();
		}
		a = value;
		isEmpty = false;
		notify();
	}

	synchronized int get() throws InterruptedException {
		if(isEmpty) {
			wait();
		}
		isEmpty = true;
		notify();

		return a;
	}




}
