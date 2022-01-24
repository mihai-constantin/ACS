package com.luxoft.effectivejava.module01.item07;

public class Main {

	public static void main(String[] args) {
		for (int i = 0; i < 3; i++) {
			new Thread(new TryCatchFinally()).start();
		}
	}

}
