package com.luxoft.effectivejava.module01.item01;

public abstract class AbstractAccount {
	private String id; 

	double balance;
        
    abstract void verifyAccount();

    public AbstractAccount(double balance){
        this.balance = balance;
    }
    
    public String getId() { 
    	return id; 
    } 
    
    public void setId(String id) { 
    	this.id = id; 
    }
    
    @Override
    public String toString(){
        return "Balance: " + (Math.round(balance * 100) / 100d);
    }
}