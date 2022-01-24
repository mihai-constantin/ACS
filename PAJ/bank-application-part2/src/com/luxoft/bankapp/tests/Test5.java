package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import java.util.HashSet;
import java.util.Set;

import org.junit.Before;
import org.junit.Test;

import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.domain.Gender;
import com.luxoft.bankapp.service.BankDataLoaderService;

public class Test5 {
	Set<Client> clients = new HashSet<Client>(); 
	String clientsFile = "files/clients.txt";
	String testSerialFile = "files/bank.ser";
	
	@Before
	public void initializeClients(){
		clients.add(new Client(("John"), Gender.MALE));
		clients.add(new Client(("Michelle"), Gender.FEMALE));
		clients.add(new Client(("James"), Gender.MALE));
		clients.add(new Client(("Brian"), Gender.MALE));
		clients.add(new Client(("Daniel"), Gender.MALE));
		clients.add(new Client(("Katherine"), Gender.FEMALE));
		clients.add(new Client(("Eugene"), Gender.MALE));
		clients.add(new Client(("Gabrielle"), Gender.FEMALE));
		clients.add(new Client(("Frank"), Gender.MALE));
		clients.add(new Client(("George"), Gender.MALE));
	}
	
	@Test
	public void testLoadFeed() {
		Bank bank = new Bank();
		BankDataLoaderService bankDataLoaderService = new BankDataLoaderService(bank);
		bankDataLoaderService.readClients(clientsFile);
		assertEquals(10, bank.getClients().size());
		assertTrue(bank.getClients().containsAll(clients));
		
		for(Client client : bank.getClients()) {
			assertEquals(1, client.getAccounts().size());
		}
	}
}
