package com.luxoft.effectivejava.module02.item11.accounts;

import java.util.HashMap;
import java.util.Map;

public class AccountCache {
	
	private static Map<String, AbstractAccount> accountsMap = new HashMap<String, AbstractAccount>(); 
	
	public static AbstractAccount cloneAccount(String accountType) { 
		AbstractAccount cachedAccount = accountsMap.get(accountType); 
		return (AbstractAccount) cachedAccount.clone(); 
	}
	
	public static void loadCache() { 
		CheckingAccount checkingAccount = new CheckingAccount(0.0, 0.0); 
		accountsMap.put("Checking account", checkingAccount); 
		
		SavingAccount savingAccount = new SavingAccount(0.0);
		accountsMap.put("Saving account", savingAccount);
		
	}
	
	public static void main(String[] args) { 
		AccountCache.loadCache(); 
		AbstractAccount clonedAccount = AccountCache.cloneAccount("Checking account"); 
		clonedAccount.verifyAccount(); 
		
		AbstractAccount clonedAccount2 = AccountCache.cloneAccount("Saving account"); 
		clonedAccount2.verifyAccount(); 
    }

}
