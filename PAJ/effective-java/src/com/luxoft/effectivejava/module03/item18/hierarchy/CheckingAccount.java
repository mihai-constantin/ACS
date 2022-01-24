package com.luxoft.effectivejava.module03.item18.hierarchy;

public class CheckingAccount extends Account {
	private double overdraft;

    public CheckingAccount(double balance, double overdraft) {
        super(balance);
        this.overdraft = Math.abs(overdraft);
    }
    
    public double maximumAmountToWithdraw(){
        return balance + overdraft;
    }
}