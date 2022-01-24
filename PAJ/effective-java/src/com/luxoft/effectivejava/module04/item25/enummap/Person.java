// Using an EnumMap to associate data with an enum
package com.luxoft.effectivejava.module04.item25.enummap;

import java.util.EnumMap;
import java.util.HashSet;
import java.util.Map;
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
		Person[] personsList = { new Person("Michael", CreditType.IMOBILIAR),
				new Person("John", CreditType.LEASING),
				new Person("Laura", CreditType.IMOBILIAR),
				new Person("Patty", CreditType.PERSONAL_NEEDS),
				new Person("Adrian", CreditType.LEASING),
				new Person("Bonnie", CreditType.PERSONAL_NEEDS) };

		// Using an EnumMap to associate data with an enum
		Map<Person.CreditType, Set<Person>> personsByCreditType = new EnumMap<Person.CreditType, Set<Person>>(
				Person.CreditType.class);
		for (Person.CreditType type : Person.CreditType.values())
			personsByCreditType.put(type, new HashSet<Person>());
		for (Person person : personsList)
			personsByCreditType.get(person.creditType).add(person);
		System.out.println(personsByCreditType);
	}
}
