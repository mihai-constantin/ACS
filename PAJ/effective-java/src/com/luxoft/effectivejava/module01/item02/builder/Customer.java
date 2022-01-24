package com.luxoft.effectivejava.module01.item02.builder;

import java.util.Date;

public class Customer {
	private Gender gender;
	private String surname;
	private String firstName;
	private String middleName;
	private Date birthday;
	private Date becomeCustomer;

	public static class Builder {
		// Required parameters
		private Gender gender;
		private String surname;
		private String firstName;

		// Optional parameters - initialized to default values
		private String middleName = null;
		private Date birthday = null;
		private Date becomeCustomer = new Date();

		public Builder(Gender gender, String surname, String firstName) {
			this.gender = gender;
			this.surname = surname;
			this.firstName = firstName;
		}

		public Builder middleName(String val) {
			middleName = val;
			return this;
		}

		public Builder birthday(Date val) {
			birthday = val;
			return this;
		}

		public Builder becomeCustomer(Date val) {
			becomeCustomer = val;
			return this;
		}

		public Customer build() {
			return new Customer(this);
		}
	}

	private Customer(Builder builder) {
		this.gender = builder.gender;
		this.surname = builder.surname;
		this.firstName = builder.firstName;
		this.middleName = builder.middleName;
		this.birthday = builder.birthday;
		this.becomeCustomer = builder.becomeCustomer;
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append(gender.getGreeting()).append(" ").append(surname).append(", ").append(firstName);
		if (null != becomeCustomer) {
			sb.append(" has become a customer on: ").append(becomeCustomer);
		}
		return sb.toString();
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

	public static void main(String[] args) {
		Customer firstClient = new Customer.Builder(Gender.MALE, "Smith", "John")
				                           .middleName("Michael")
				                           .becomeCustomer(new Date())
				                           .birthday(new Date())
				                           .build();
		System.out.println(firstClient);
	}

}
