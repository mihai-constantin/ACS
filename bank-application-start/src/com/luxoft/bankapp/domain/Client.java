package com.luxoft.bankapp.domain;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.util.*;

public class Client {
	
	private String name;
	private Gender gender;
	private String city;
	private Set<Account> accounts = new LinkedHashSet<>();

	private LocalDate birthday;

	public Client(String name, Gender gender) {
		this.name = name;
		this.gender = gender;
	}

	public Client(String name, Gender gender, String city) {
		this.name = name;
		this.gender = gender;
		this.city = city;
	}

	public Client(String name, Gender gender, LocalDate birthday) {
		this.name = name;
		this.gender = gender;
		this.birthday = birthday;
	}

	public void addAccount(final Account account) {
		accounts.add(account);
	}
	
	public String getName() {
		return name;
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

	public LocalDate getBirthday() {
		return birthday;
	}

	public int getBirthdayMonth() {
		return birthday.getMonth().getValue();
	}

	public long daysUntilBirthday() {
		LocalDate today = LocalDate.now();
		long daysInBetween = ChronoUnit.DAYS.between(today, LocalDate.of(today.getYear(), birthday.getMonth(), birthday.getDayOfMonth()));
		if (daysInBetween < 0) {
			daysInBetween = 365 + daysInBetween;
		}
		return daysInBetween;
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
