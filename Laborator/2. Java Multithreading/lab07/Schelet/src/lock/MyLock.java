package lock;

import java.util.concurrent.atomic.AtomicInteger;

public class MyLock {
	private AtomicInteger sw = new AtomicInteger(1);
	
	void lock() {
		while(!sw.compareAndSet(1, 0))
			;
	}
	
	void unlock() {
		sw.set(1);
	}
}
