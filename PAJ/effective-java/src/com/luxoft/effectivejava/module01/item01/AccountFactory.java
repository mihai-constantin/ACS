package com.luxoft.effectivejava.module01.item01;

public class AccountFactory {
	
	public static AbstractAccount newAccount(String accountType) {
		if(accountType == null){ 
			return null; 
		}
		
		switch(accountType.toUpperCase()) {
		    case "CHECKING":
		    	return new CheckingAccount(0.0, 0.0); 
		    case "SAVING":
		    	return new SavingAccount(0.0);
		    default:
		    	return null;
		}
		
	}
	
	public static void main(String[] args) { 
		//get an object of CheckingAccount 
		AbstractAccount account1 = AccountFactory.newAccount("CHECKING");
		System.out.println(account1.getClass().getSimpleName()); 
		
		//get an object of SavingAccount 
		AbstractAccount account2 = AccountFactory.newAccount("SAVING"); 
		System.out.println(account2.getClass().getSimpleName()); 
		
	}

}
