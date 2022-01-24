package com.luxoft.effectivejava.module01.item03.staticfactory;

//Singleton with static factory
public class Bank {
	
	private static final Bank INSTANCE = new Bank();
	private Bank() {
		
	}

	public static Bank getInstance() { 
		return INSTANCE; 
	}
}

