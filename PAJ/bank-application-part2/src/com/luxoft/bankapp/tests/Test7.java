package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.SortedSet;

import org.junit.Before;
import org.junit.Test;

import com.luxoft.bankapp.domain.Account;
import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.domain.Gender;
import com.luxoft.bankapp.service.BankDataLoaderService;
import com.luxoft.bankapp.service.BankReport;

public class Test7 {
	
	String clientsFile = "files/clients.txt";
	Bank bank = new Bank();
	BankReport bankReport;
	
	@Before
	public void initialize(){
		BankDataLoaderService bankDataLoaderService = new BankDataLoaderService(bank);
		bankDataLoaderService.readClients(clientsFile);
		bankReport = new BankReport(bank);
	}
	
	@Test
	public void testNumberOfClients() {
		assertEquals(10, bankReport.getNumberOfClients());
	}
	
	
	@Test
	public void testNumberOfAccounts() {
		assertEquals(10, bankReport.getNumberOfAccounts());
	}
	
	@Test
	public void testClientsSorted() {
		SortedSet<Client> clients = bankReport.getClientsSorted();
		
		assertEquals(10, clients.size());
		assertTrue(clients.first().equals(new Client(("Brian"), Gender.MALE)));
		assertTrue(clients.last().equals(new Client(("Michelle"), Gender.FEMALE)));
	}
	
	@Test
	public void testBankCreditSum() {
		assertEquals(1477.9, bankReport.getBankCreditSum(), 0);
	}
	
	@Test
	public void testCustomerAccounts() {
		Map<Client, Collection<Account>>  customerAccounts = bankReport.getCustomerAccounts();
		
		assertEquals(10, customerAccounts.size());
		assertEquals("Saving account 4, balance: 487.72", customerAccounts.get(new Client(("Brian"), Gender.MALE)).iterator().next().toString());
	}
	
	@Test
	public void testClientsByCity() {
		Map<String, ArrayList<Client>> clientsByCity = bankReport.getClientsByCity();
		
		assertEquals(2, clientsByCity.get("New York").size());
		assertEquals(8, clientsByCity.get("Boston").size());
	}
	

}
