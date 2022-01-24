package com.luxoft.effectivejava.module03.item19.clientfinder;

import java.io.Serializable;

public class Client implements Serializable {

	private static final long serialVersionUID = 4067471219340550144L;
	
	private String name;
	private Gender gender;
	private int age;

	public Client(String name, Gender gender, int age) {
		this.name = name;
		this.gender = gender;
		this.age = age;
	}
	
	public String getName() {
		return name;
	}
	
	public Gender getGender() {
		return gender;
	}
	
	public int getAge() {
		return age;
	}
	
	public String getSalutation() {
		if (gender != null) {
			return gender.getSalute() + " " + name;
		} else {
			return name;
		}
	}
	
	@Override
	public String toString() {
		StringBuffer client = new StringBuffer(getSalutation());
		return client.toString();
	}
}
