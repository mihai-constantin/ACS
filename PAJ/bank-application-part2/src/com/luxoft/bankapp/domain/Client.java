package com.luxoft.bankapp.domain;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

import com.luxoft.bankapp.utils.Params;

public class Client implements Serializable {
		
	private static final long serialVersionUID = -6343841891631428291L;
	private String name;
	private Gender gender;
	private String phoneAreaCode;
	private String phoneNumber;
	
	private Set<Account> accounts = new HashSet<Account>();
	private String city;

	public Client(String name, Gender gender) {
		this(name, gender, new ArrayList<Account>());
	}
	
	public Client(String name, Gender gender, Collection<Account> accounts) {
		this.name = name;
		this.gender = gender;
		this.accounts.addAll(accounts);
	}
	
	public Client(String name, Gender gender, Account[] accounts){
        this(name, gender, Arrays.asList(accounts));
    }
	
	public Client(final String name, final Gender gender, Account account) {
		this(name, gender, new Account[]{account});
	}
	
	public Set<Account> getAccounts() {
		return accounts;
	}
	
	public void setAccounts(Set<Account> accounts) {
		this.accounts = accounts;
	}
	
	public String getName() {
		return name;
	}
	
	public Gender getGender() {
		return gender;
	}
	
	public String getCity() {
		return city;
	}

	public void setCity(String city) {
		this.city = city;
	}
	
	public String getPhoneAreaCode() {
		return phoneAreaCode;
	}
	
	public void setPhoneAreaCode(String phoneAreaCode) {
		this.phoneAreaCode = phoneAreaCode;
	}

	public String getPhoneNumber() {
		return phoneNumber;
	}

	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
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
		StringBuilder sb = new StringBuilder();
		
		sb.append(getClientGreeting())
		  .append("\n")
		  .append("City: " + getCity())
		  .append("\n")
		  .append("phoneAreaCode: " + getPhoneAreaCode())
		  .append("\n")
		  .append("phoneNumber: " + getPhoneNumber())
		  .append("\n");
		
		for (Account account : getAccounts()) {
			sb.append(account)
			  .append("\n");
		}
		return sb.toString();
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((gender == null) ? 0 : gender.hashCode());
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Client other = (Client) obj;
		if (gender != other.gender)
			return false;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}
	
	public static Client parseClient(String str){
		Params params = new Params(str.split(";"));
		
        Client client = new Client(
                params.get("name"),
                Gender.parse(params.get("gender")),
                AbstractAccount.parse(params));
        
        client.setCity(params.get("city"));

        return client;
    }
}
