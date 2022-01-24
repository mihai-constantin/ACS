package com.luxoft.effectivejava.module03.item19.clientfinder;

import java.util.ArrayList;
//import java.util.Collections;
//import java.util.Comparator;
import java.util.List;

public class StrategyDemo {
	
	public static void main(String[] args) {
		Client john = new Client("John", Gender.MALE, 38);
		Client richard = new Client("Richard", Gender.MALE, 27);
		Client laura = new Client("Laura", Gender.FEMALE, 34);
		
		Bank bank = new Bank();
		bank.addClient(john);
		bank.addClient(richard);
		bank.addClient(laura);
		
		List<Client> clientsList = new ArrayList<Client>(bank.getClients());
		
		List<Client> resultList = ClientFinder.findClients(clientsList, new Strategy() {

			@Override
			public boolean acceptClient(Client client) {
				return client.getName().startsWith("L");
			}
			
		});
		
		
		for(Client client : resultList) {
			System.out.print(client.getName() + ", ");
        }
		
		System.out.println();
		
		resultList = ClientFinder.findClients(clientsList, new Strategy() {

			@Override
			public boolean acceptClient(Client client) {
				return client.getGender().equals(Gender.MALE);
			}
			
		});
		
		
		for(Client client : resultList) {
			System.out.print(client.getName() + ", ");
        }
	}

}

