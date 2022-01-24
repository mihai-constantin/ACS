package com.luxoft.effectivejava.module01.item02.telescoping;


import java.util.Date;

public class Customer {
	private Gender gender;
	private String surname;
	private String firstName;
	private String middleName;
	private Date birthday;
	private Date becomeCustomer;
	
	public Customer(Gender gender, String surname, String firstName) {
		this(gender, surname, firstName, null);
	}
	
	public Customer(Gender gender, String surname, String firstName, String middleName) {
		this(gender, surname, firstName, middleName, null);
	}
	
	public Customer(Gender gender, String surname, String firstName, String middleName, Date birthday) {
		this(gender, surname, firstName, middleName, birthday, null);
	}
	
	public Customer(Gender gender, String surname, String firstName, String middleName, Date birthday, Date becomeCustomer) {
		this.gender = gender;
		this.surname = surname;
		this.firstName = firstName;
		this.middleName = middleName;
		this.birthday = birthday;
		this.becomeCustomer = becomeCustomer;
	}
	
	public Gender getGender() {
		return gender;
	}

	public String getSurname() {
		return surname;
	}

	public String getFirstName() {
		return firstName;
	}

	public String getMiddleName() {
		return middleName;
	}

	public Date getBirthday() {
		return birthday;
	}

	public Date getBecomeCustomer() {
		return becomeCustomer;
	}
	
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(gender.getGreeting())
		  .append(" ")
		  .append(surname)
		  .append(", ")
		  .append(firstName);
		return sb.toString();
	}
	
	public static void main (String[] args) {
		Customer firstClient = new Customer(Gender.MALE, "Smith", "John", null, null, new Date());
		System.out.println(firstClient);
	}

}
