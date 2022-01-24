// Using an EnumMap to associate data with an enum
package com.luxoft.effectivejava.module04.item25.ordinal;

import java.util.HashSet;
import java.util.Set;

public class Person {
	public enum CreditType {
		IMOBILIAR, PERSONAL_NEEDS, LEASING
	}

	private final String name;
	private final CreditType creditType;

	public Person(String name, CreditType creditType) {
		this.name = name;
		this.creditType = creditType;
	}

	@Override
	public String toString() {
		return name;
	}

	public static void main(String[] args) {
		Person[] personsList = { new Person("Michael", CreditType.IMOBILIAR), new Person("John", CreditType.LEASING),
				new Person("Laura", CreditType.IMOBILIAR), new Person("Patty", CreditType.PERSONAL_NEEDS),
				new Person("Adrian", CreditType.LEASING), new Person("Bonnie", CreditType.PERSONAL_NEEDS) };

		@SuppressWarnings("unchecked")
		Set<Person>[] personsByCreditType = (Set<Person>[]) new Set[Person.CreditType.values().length];
		for (int i = 0; i < personsByCreditType.length; i++) {
			personsByCreditType[i] = new HashSet<Person>();
		}

		for (Person person : personsList) {
			personsByCreditType[person.creditType.ordinal()].add(person);
		}

		// Print the results
		for (int i = 0; i < personsByCreditType.length; i++) {
			System.out.printf("%s: %s%n", Person.CreditType.values()[i], personsByCreditType[i]);
		}
	}
}
