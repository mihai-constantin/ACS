package com.luxoft.bankapp.domain;

import com.luxoft.bankapp.employees.BankEmployee;

public class Department {
	private String name;
	private BankEmployee manager;
	
	public Department(String name) {
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public BankEmployee getManager() {
		return manager;
	}
	
	public void setManager(BankEmployee manager) {
		this.manager = manager;
	}
	
	@Override
	public String toString() {
		return name;
	}

}
