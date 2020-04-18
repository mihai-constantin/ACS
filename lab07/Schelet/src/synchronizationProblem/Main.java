package synchronizationProblem;
/**
 * @author cristian.chilipirea
 *
 */
public class Main {
	static final int N = 100000;
	static int N_ITERATIONS = 100;

	public static void main(String[] args) {
		Thread threads[] = new Thread[2];
		boolean sw = true;
		System.out.println("Synchronization problem. Do not solve me with locks");		
		
		for (int j = 0; j < N_ITERATIONS; j++) {
//			MyThread.value = 0;
			MyThread.value.set(0);
			for (int i = 0; i < 2; i++)
				threads[i] = new Thread(new MyThread(i));
			for (int i = 0; i < 2; i++)
				threads[i].start();
			for (int i = 0; i < 2; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			if (MyThread.value.get() != 2 * 3 * N) {
				System.out.println("i was different than " + 2 * 3 * N + ", it is " + MyThread.value);
				sw = false;
			}
		}
		if (sw)
			System.out.println("Correct");
	}
}
