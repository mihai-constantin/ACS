package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Before;
import org.junit.Test;

import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.SavingAccount;
import com.luxoft.bankapp.exceptions.NotEnoughFundsException;

public class Test4 {
	SavingAccount savingAccount1;
	SavingAccount savingAccount2;
	CheckingAccount checkingAccount1;
	CheckingAccount checkingAccount2;
	
	@Before
	public void initializeAccounts(){
		savingAccount1 = new SavingAccount(1, 1140.25);
		savingAccount2 = new SavingAccount(1, 1140.25);
		
		checkingAccount1 = new CheckingAccount(2, 1120.75, 100.0);
		checkingAccount2 = new CheckingAccount(2, 1120.75, 100.0);
		
	}
	
	@Test
	public void testEqualAccounts() throws NotEnoughFundsException {
		assertTrue(savingAccount1.equals(savingAccount2));
		assertFalse(savingAccount1 == savingAccount2);
		
		assertTrue(checkingAccount1.equals(checkingAccount2));
		assertFalse(checkingAccount1 == checkingAccount2);
		
		SavingAccount savingAccount3 = new SavingAccount(3, 1140.25);
		assertFalse(savingAccount1.equals(savingAccount3));
		assertFalse(savingAccount1 == savingAccount3);
		
		CheckingAccount checkingAccount4 = new CheckingAccount(4, 1120.75, 100.0);
		assertFalse(checkingAccount1.equals(checkingAccount4));
		assertFalse(checkingAccount1 == checkingAccount4);
	}
	
	@Test
	public void testAccountsToString() throws NotEnoughFundsException {
		assertEquals("Saving account 1, balance: 1140.25", savingAccount1.toString());
		assertEquals("Checking account 2, balance: 1120.75, overdraft: 100.00", checkingAccount1.toString());
	}
	
	@Test
	public void testAccountsToDecimal() throws NotEnoughFundsException {
		assertEquals(1140, savingAccount1.decimalValue());
		assertEquals(1121, checkingAccount1.decimalValue());
	}

}
