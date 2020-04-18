package lock;

/**
 * @author cristian.chilipirea
 * 
 */
public class MyThread implements Runnable {
	int id;
	static int value = 0;
	MyLock lock;

	MyThread(int id, MyLock lock) {
		this.id = id;
		this.lock = lock;
	}

	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++) {
				lock.lock();
				value = value + 3;
				lock.unlock();
			}
		} else {
			for (int i = 0; i < Main.N; i++) {
				lock.lock();
				value = value + 3;
				lock.unlock();
			}
		}
	}
}
