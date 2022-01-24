package com.luxoft.effectivejava.module03.item19.client;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class Client implements Serializable {

	private static final long serialVersionUID = 4067471219340550144L;

	private String name;
	private int age;

	public Client(String name, int age) {
		this.name = name;
		this.age = age;
	}

	public String getName() {
		return name;
	}
	
	@Override
	public String toString() {
		return name + " " + age;
	}

	static class ClientAgeComparator implements Comparator<Client> {
		public int compare(Client client1, Client client2) {
			return client1.age - client2.age;
		}
	}

	public static void main(String[] args) {
		Client laura = new Client("Laura", 34);
		Client john = new Client("John", 38);
		Client richard = new Client("Richard", 27);

		List<Client> clientsList = new ArrayList<Client>();

		clientsList.add(john);
		clientsList.add(richard);
		clientsList.add(laura);
		
		clientsList.sort(new ClientAgeComparator());
		
		for(Client client: clientsList) {
			System.out.println(client);
		}

	}

}
