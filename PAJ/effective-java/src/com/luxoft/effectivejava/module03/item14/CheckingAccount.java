// Encapsulation of data by accessor methods and mutators
package com.luxoft.effectivejava.module03.item14;

class CheckingAccount {
	private int id;
	private double balance; 
	private double overdraft;
	
	public int getId() {
		return id;
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public double getBalance() {
		return balance;
	}
	
	public void setBalance(double balance) {
		this.balance = balance;
	}
	
	public double getOverdraft() {
		return overdraft;
	}
	
	public void setOverdraft(double overdraft) {
		this.overdraft = overdraft;
	}
}
