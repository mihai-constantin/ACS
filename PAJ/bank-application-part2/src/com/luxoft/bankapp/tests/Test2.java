package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;

import java.util.HashSet;
import java.util.Set;

import org.junit.Test;

import com.luxoft.bankapp.domain.Account;
import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.domain.Gender;
import com.luxoft.bankapp.domain.SavingAccount;
import com.luxoft.bankapp.exceptions.ClientExistsException;
import com.luxoft.bankapp.service.BankService;

public class Test2 {
	
	@Test
	public void testBank() throws ClientExistsException {
		Bank bank = new Bank();
		Client client1 = new Client("Smith John", Gender.MALE); 
		Set<Account> accounts1 = new HashSet<Account>();
		accounts1.add(new SavingAccount(1, 1000.0));
		accounts1.add(new CheckingAccount(2, 1000.0, 100.0));
		client1.setAccounts(accounts1);
		
		Client client2 = new Client("Smith Michelle", Gender.FEMALE); 
		Set<Account> accounts2 = new HashSet<Account>();
		accounts2.add(new SavingAccount(3, 2000.0));
		accounts2.add(new CheckingAccount(4, 1500.0, 200.0));
		client2.setAccounts(accounts2);
		
		BankService.addClient(bank, client1);
		BankService.addClient(bank, client2);
		
		assertEquals(2, bank.getClients().size());
	}

}

