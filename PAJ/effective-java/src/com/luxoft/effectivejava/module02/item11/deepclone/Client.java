package com.luxoft.effectivejava.module02.item11.deepclone;

import java.io.Serializable;

public class Client implements Serializable, Cloneable {

	private static final long serialVersionUID = 4067471219340550144L;

	private String name;
	private Account account;

	public Client(String name, Account account) {
		this.name = name;
		this.account = account;
	}

	public String getName() {
		return name;
	}

	public Account getAccount() {
		return account;
	}

	@Override
	public Client clone() {
		Client clone = null;
		try {
			clone = (Client)super.clone();
			clone.account = account.clone();
		} catch (CloneNotSupportedException e) {
			e.printStackTrace();
		}
		return clone;
	}

	public static void main(String[] args) {
		Account account = new Account(1, 1000);
		Client michael = new Client("Michael", account);

		Client clonedMichael = (Client) michael.clone();
		
		System.out.println(michael.equals(clonedMichael));
		System.out.println(michael.getAccount().equals(clonedMichael.getAccount()));
		System.out.println(michael.getAccount() == clonedMichael.getAccount());

	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((account == null) ? 0 : account.hashCode());
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
		if (account == null) {
			if (other.account != null)
				return false;
		} else if (!account.equals(other.account))
			return false;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}

}
