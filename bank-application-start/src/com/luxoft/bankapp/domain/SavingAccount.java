package com.luxoft.bankapp.domain;


public class SavingAccount extends AbstractAccount {
	public SavingAccount(int id, double balance) {
		super(id, balance);
	}
	
	public double maximumAmountToWithdraw(){
        return getBalance();
    }

	@Override
	public String toString() {
		return "SavingAccount{" +
				"balance=" + balance +
				'}';
	}
}
