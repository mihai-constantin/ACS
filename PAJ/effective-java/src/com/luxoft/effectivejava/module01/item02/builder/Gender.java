package com.luxoft.effectivejava.module01.item02.builder;

public enum Gender {
	MALE("Mr."), FEMALE("Ms.");

	private String greeting;

	private Gender(final String greeting) {
		this.greeting = greeting;
	}

	public String getGreeting() {
		return greeting;
	}
}
