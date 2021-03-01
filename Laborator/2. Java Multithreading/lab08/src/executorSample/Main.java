package executorSample;

/**
 * @author cristian.chilipirea
 * 
 * This program should print SOME of the numbers between 0 and 10.
 * Because of the way we shutdown the ExecutorService some tasks do not get submitted.
 * This is OK in cases where we want to find at least one solution, but not necessarily all solutions.
 */

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

	public static void main(String[] args) {
		ExecutorService tpe = Executors.newFixedThreadPool(4);
		tpe.submit(new MyRunnable(tpe, 0));
		tpe.submit(new MyRunnable(tpe, 1));
		tpe.submit(new MyRunnable(tpe, 2));
	}
}
