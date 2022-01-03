package com.luxoft.bankapp.tests;

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

public class Test3 {
	
	@Test(expected=IllegalArgumentException.class)
	public void testCreateCheckingAccount() {
		new CheckingAccount(1, 1000.0, -100.0);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testDepositNegativeValue() {
		SavingAccount savingAccount = new SavingAccount(1, 1000.0);
		savingAccount.deposit(-100.0);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testWithdrawNegativeValue() throws OverdraftLimitExceededException {
		CheckingAccount checkingAccount = new CheckingAccount(2, 1000.0, 100.0);
		checkingAccount.withdraw(-100.0);
	}
	
	@Test(expected=NotEnoughFundsException.class)
	public void testSavingAccountThrowException() throws NotEnoughFundsException {
		SavingAccount savingAccount = new SavingAccount(1, 1000.0);
		savingAccount.deposit(100.0);
		savingAccount.withdraw(2000.0);
	}
	
	@Test(expected=OverdraftLimitExceededException.class)
	public void testCheckingAccountThrowException() throws OverdraftLimitExceededException {
		CheckingAccount checkingAccount = new CheckingAccount(2, 1000.0, 100.0);
		checkingAccount.deposit(100.0);
		checkingAccount.withdraw(2000.0);
	}
	
	@Test(expected=ClientExistsException.class)
	public void testClientExists() throws ClientExistsException {
		Bank bank = new Bank();
		Client client1 = new Client("Smith John", Gender.MALE); 
		client1.addAccount(new SavingAccount(1, 1000.0));
		client1.addAccount(new CheckingAccount(2, 1000.0, 100.0));
		
		BankService.addClient(bank, client1);
		BankService.addClient(bank, client1);
		
	}

}
