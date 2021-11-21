package com.luxoft.bankapp.domain;

import java.util.*;

public class Client {
	
	private String name;
	private Gender gender;
	private String city;
	private Set<Account> accounts = new LinkedHashSet<>();

	public Client(String name, Gender gender) {
		this.name = name;
		this.gender = gender;
	}

	public Client(String name, Gender gender, String city) {
		this.name = name;
		this.gender = gender;
		this.city = city;
	}

	public void addAccount(final Account account) {
		accounts.add(account);
	}
	
	public String getName() {
		return name;
	}
	
	public Gender getGender() {
		return gender;
	}
	
	public Set<Account> getAccounts() {
		return Collections.unmodifiableSet(accounts);
	}
	
	public String getClientGreeting() {
		if (gender != null) {
			return gender.getGreeting() + " " + name;
		} else {
			return name;
		}
	}
	
	@Override
	public String toString() {
		return getClientGreeting();
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) return true;
		if (!(o instanceof Client)) return false;
		Client client = (Client) o;
		return Objects.equals(name, client.name) && gender == client.gender;
	}

	@Override
	public int hashCode() {
		return Objects.hash(name, gender);
	}

	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}
}
