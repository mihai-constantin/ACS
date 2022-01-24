package com.luxoft.effectivejava.module03.item18.hierarchy;

public class SavingAccount extends Account {
	public SavingAccount(double balance) {
        super(balance);
    }
	
	public double maximumAmountToWithdraw(){
        return balance;
    }
}