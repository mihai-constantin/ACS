package com.luxoft.effectivejava.module02.item11.accounts;

public abstract class AbstractAccount {
	double balance;
        
    abstract void verifyAccount();

    public AbstractAccount(double balance){
        this.balance = balance;
    }
    
    @Override
    public Object clone() { 
    	Object clone = null; 
    	try { 
    		clone = super.clone(); 
    	} catch (CloneNotSupportedException e) { 
    		e.printStackTrace(); 
    	} 
    	return clone; 
    }
}