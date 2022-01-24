package com.luxoft.effectivejava.module01.item02.javabeans;

import java.util.Date;

public class Customer {
	private Gender gender;
	private String surname;
	private String firstName;
	private String middleName;
	private Date birthday;
	private Date becomeCustomer;
	
	public Customer(Gender gender, String surname, String firstName) {
		this.gender = gender;
		this.surname = surname;
		this.firstName = firstName;
	}
	
	public void setGender(Gender gender) {
		this.gender = gender;
	}

	public void setSurname(String surname) {
		this.surname = surname;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}
	
	public String getMiddleName() {
		return middleName;
	}

	public void setMiddleName(String middleName) {
		this.middleName = middleName;
	}
	
	public Date getBirthday() {
		return birthday;
	}

	public void setBirthday(Date birthday) {
		this.birthday = birthday;
	}
	
	public Date getBecomeCustomer() {
		return becomeCustomer;
	}

	public void setBecomeClient(Date becomeCustomer) {
		this.becomeCustomer = becomeCustomer;
	}

	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(gender.getGreeting())
		  .append(" ")
		  .append(surname)
		  .append(", ")
		  .append(firstName);
		if (null != becomeCustomer) {
			sb.append(" has become a customer on: ")
			  .append(becomeCustomer);
		}
		return sb.toString();
	}
	
	public static void main (String[] args) {
		Customer firstClient = new Customer(Gender.MALE, "Smith", "John");
		firstClient.setBecomeClient(new Date());
		System.out.println(firstClient);
	}

}
