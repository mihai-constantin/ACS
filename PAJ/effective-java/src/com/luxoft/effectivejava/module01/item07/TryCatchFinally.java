package com.luxoft.effectivejava.module01.item07;

public class TryCatchFinally implements Runnable {

	private void testMethod() {
		try {
			System.out.println("In try block");
			throw new RuntimeException();
		} catch (RuntimeException exception) {
			System.out.println("In catch block");
		} finally {
			System.out.println("In finally block");
		}
	}

	@Override
	protected void finalize() throws Throwable {
		System.out.println("In finalize block");
		super.finalize();
	}

	@Override
	public void run() {
		testMethod();
	}

}
