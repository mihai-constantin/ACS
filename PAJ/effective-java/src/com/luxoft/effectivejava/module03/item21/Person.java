package com.luxoft.effectivejava.module03.item21;

import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Calendar;
import java.util.Date;

public class Person {

	private String name;
	private Date birthday;

	public Date getBirthday() {
		return birthday;
	}

	public void setBirthday(Date birthday) {
		this.birthday = birthday;
	}

	private static int setRandomYear() {
		return (int) (2000 + 14 * Math.random());
	}

	private static int setRandomMonth() {
		return (int) (12 * Math.random());
	}

	public static int compareByAge(Person a, Person b) {
		return a.birthday.compareTo(b.birthday);
	}

	public void printPerson() {
		SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
		System.out.format("%s %s%n", this.name, dateFormat.format(this.birthday));
	}

	private static void populatePersons(String[] stringArray, Person[] personArray) {
		Calendar cal = Calendar.getInstance();

		for (int i = 0; i < stringArray.length; i++) {
			personArray[i] = new Person();
			cal.set(Calendar.YEAR, setRandomYear());
			cal.set(Calendar.MONTH, setRandomMonth());
			cal.set(Calendar.DAY_OF_MONTH, 1);
			personArray[i].name = stringArray[i];
			personArray[i].birthday = cal.getTime();
		}
		System.out.println();
	}

	private static void displayPersonsAndBirthdays(Person[] personArray) {
		for (Person person : personArray) {
			person.printPerson();
		}
		System.out.println();
	}

	private static void orderAndDisplayStrings(String[] stringArray) {
		Arrays.sort(stringArray, String::compareToIgnoreCase);

		for (String name : stringArray) {
			System.out.println(name);
		}
	}
	
	public static void main(String[] args) {
		String[] stringArray = { "Barbara", "James", "Mary", "John", "Patricia", "Robert", "Michael", "Linda" };
		orderAndDisplayStrings(stringArray);

		Person[] personArray = new Person[stringArray.length];
		populatePersons(stringArray, personArray);

		Arrays.sort(personArray, (a, b) -> {
			return a.getBirthday().compareTo(b.getBirthday());
		});
		displayPersonsAndBirthdays(personArray);

		Arrays.sort(personArray, (a, b) -> Person.compareByAge(a, b));
		displayPersonsAndBirthdays(personArray);

		Arrays.sort(personArray, Person::compareByAge);
		displayPersonsAndBirthdays(personArray);

	}

}
