package com.luxoft.effectivejava.module02.item11.deepclone;

public class Account implements Cloneable {

	private int id;
	double balance;

	public Account(int id, double balance){
		this.id = id;
        this.balance = balance;
    }
	
	public int getId() {
		return id;
	}

	public double getBalance() {
		return balance;
	}
	
	public Account clone() throws CloneNotSupportedException {
		return (Account) super.clone();
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Account other = (Account) obj;
		if (Double.doubleToLongBits(balance) != Double.doubleToLongBits(other.balance))
			return false;
		if (id != other.id)
			return false;
		return true;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		long temp;
		temp = Double.doubleToLongBits(balance);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		result = prime * result + id;
		return result;
	}

}
