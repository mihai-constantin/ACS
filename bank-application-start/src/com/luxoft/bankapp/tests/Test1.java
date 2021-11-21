package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.domain.Gender;
import com.luxoft.bankapp.domain.SavingAccount;
import com.luxoft.bankapp.exceptions.ClientExistsException;
import com.luxoft.bankapp.exceptions.NotEnoughFundsException;
import com.luxoft.bankapp.exceptions.OverdraftLimitExceededException;
import com.luxoft.bankapp.service.BankService;

import java.util.ArrayList;

public class Test1 {
	
	@Test
	public void testSavingAccount() throws NotEnoughFundsException {
		SavingAccount savingAccount = new SavingAccount(1, 1000.0);
		savingAccount.deposit(100.0);
		savingAccount.withdraw(50.0);
		assertEquals(1, savingAccount.getId());
		assertEquals(1050, savingAccount.getBalance(), 0);
		assertEquals(1050, savingAccount.maximumAmountToWithdraw(), 0);
	}
	
	@Test
	public void testCheckingAccount() throws OverdraftLimitExceededException {
		CheckingAccount checkingAccount = new CheckingAccount(2, 1000.0, 100.0);
		checkingAccount.deposit(100.0);
		checkingAccount.withdraw(1150.0);
		assertEquals(2, checkingAccount.getId());
		assertEquals(-50, checkingAccount.getBalance(), 0);
		assertEquals(100, checkingAccount.getOverdraft(), 0);
		assertEquals(50, checkingAccount.maximumAmountToWithdraw(), 0);
	}
	
	@Test
	public void testClient() {
		Client client = new Client("Smith John", Gender.MALE); 
		client.addAccount(new SavingAccount(1, 1000.0));
		client.addAccount(new CheckingAccount(2, 1000.0, 100.0));
		assertEquals(2, client.getAccounts().size());
		assertEquals("Mr. Smith John", client.getClientGreeting());
		assertEquals("Mr. Smith John", client.toString());
	}
	
	@Test
	public void testBank() throws ClientExistsException {
		Bank bank = new Bank();
		Client client1 = new Client("Smith John", Gender.MALE); 
		client1.addAccount(new SavingAccount(1, 1000.0));
		client1.addAccount(new CheckingAccount(2, 1000.0, 100.0));
		
		Client client2 = new Client("Smith Michelle", Gender.FEMALE); 
		client2.addAccount(new SavingAccount(3, 2000.0));
		client2.addAccount(new CheckingAccount(4, 1500.0, 200.0));
		
		BankService.addClient(bank, client1);
		BankService.addClient(bank, client2);
		
		assertEquals(2, bank.getClients().size());
		assertEquals("Mr. Smith John", new ArrayList<>(bank.getClients()).get(0).getClientGreeting());
		assertEquals("Mr. Smith John", new ArrayList<>(bank.getClients()).get(0).toString());
		assertEquals("Ms. Smith Michelle", new ArrayList<>(bank.getClients()).get(1).getClientGreeting());
		assertEquals("Ms. Smith Michelle", new ArrayList<>(bank.getClients()).get(1).toString());
	}

}
