package com.luxoft.bankapp.employees;

import com.luxoft.bankapp.domain.Department;

public class BankEmployee {

	protected String name;
	protected Department department;
	protected int salary;
	
	public BankEmployee() {
		
	}

	public BankEmployee(String name, Department department, int salary) { 
		this.name = name; 
		this.department = department; 
		this.salary = salary; 
	}
	
	public Department getDepartment() {
		return department;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void setDepartment(Department department) {
		this.department = department;
	}

	public int getSalary() {
		return salary;
	}

	public void setSalary(int salary) {
		this.salary = salary;
	}
}
