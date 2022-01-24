package com.luxoft.effectivejava.module03.item18.hierarchy;


public abstract class Account {
	double balance;
        
    abstract double maximumAmountToWithdraw();
    
    public Account(double balance){
        this.balance = balance;
    }
}