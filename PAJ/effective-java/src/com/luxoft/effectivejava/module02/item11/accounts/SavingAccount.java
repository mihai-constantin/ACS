package com.luxoft.effectivejava.module02.item11.accounts;

public class SavingAccount extends AbstractAccount {
	public SavingAccount(double balance) {
        super(balance);
    }
	
	@Override
    public void verifyAccount(){
		System.out.format("Saving account, balance = %.2f%n", balance);
    }

}