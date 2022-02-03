package com.mihai.libraryapp.main;

import com.mihai.libraryapp.domain.*;
import com.mihai.libraryapp.exceptions.AlreadyBorrowedBookException;
import com.mihai.libraryapp.exceptions.ClientExistsException;
import com.mihai.libraryapp.report.ILibraryReport;
import com.mihai.libraryapp.report.LibraryReport;
import com.mihai.libraryapp.report.LibraryReportStreams;
import com.mihai.libraryapp.service.LibraryService;

import java.util.Arrays;
import java.util.HashSet;
import java.util.SortedSet;

public class LibraryApplication {
	
	private static Library library;
	
	public static void main(String[] args) {
		library = new Library();
		modifyBank();

		if (args.length > 0 && args[0].equals("-statistics")) {
			System.out.println();
			printStatistics();
		}

		try {
			library.getEmailService().close();
		} catch (InterruptedException interruptedException) {
			interruptedException.printStackTrace();
		}
	}
	
	private static void modifyBank() {
		Client client1 = new Client("Mihai", Gender.MALE, "Bucharest");
		Client client2 = new Client("Anna", Gender.FEMALE, "London");
		Client client3 = new Client("Emily", Gender.FEMALE, "Berlin");

		try {
		   LibraryService.addClient(library, client1);
		} catch(ClientExistsException e) {
			System.out.format("Cannot add an already existing client: %s%n", client1.getName());
	    } 

		try {
		  LibraryService.addClient(library, client1);
		} catch(ClientExistsException e) {
		  System.out.format("Cannot add an already existing client: %s%n", client1);
	    }

		try {
			LibraryService.addClient(library, client2);
		} catch(ClientExistsException e) {
			System.out.format("Cannot add an already existing client: %s%n", client2);
		}

		try {
			LibraryService.addClient(library, client3);
		} catch(ClientExistsException e) {
			System.out.format("Cannot add an already existing client: %s%n", client3);
		}

		// books logic
		IBook novel = new Novel(1, "Les Miserables", 852, 20, "Victor Hugo", "Penguin");
		IBook magazine = new Magazine(2, "Vogue", 30, 5);
		IBook article = new Article(3, "FFT", 10, 3, new HashSet<>(Arrays.asList("Huang", "Sam", "Alex")));

		try {
			client1.addBook(novel);
		} catch (AlreadyBorrowedBookException e) {
			System.out.format("[Message for client %s]: ", client1.getName());
			System.out.println(e.getMessage());
		}

		try {
			client1.addBook(magazine);
			client1.addBook(article);
		} catch (AlreadyBorrowedBookException e) {
			e.printStackTrace();
		}

		try {
			client2.addBook(novel);
		} catch (AlreadyBorrowedBookException e) {
			System.out.format("[Message for client %s]: ", client2.getName());
			System.out.println(e.getMessage());
		}
	}
	
	private static void printStatistics() {
		printReport(new LibraryReport());

		System.out.println();
		System.out.println();

		printReport(new LibraryReportStreams());
	}

	public static void printReport(ILibraryReport report) {
		System.out.println("numberOfClients: " + report.getNumberOfClients(library));
		System.out.println("sortedSet: " + report.getClientsSorted(library));
		System.out.println("getClientsByCity: " + report.getClientsByCity(library));
		System.out.println("numberOfBorrowedBooks: " + report.getNumberOfBorrowedBooks(library));

		SortedSet<IBook> borrowedBooksSortedByName = report.getBorrowedBooksSortedByName(library);
		System.out.println("=== Borrowed Books ===");
		for (IBook book : borrowedBooksSortedByName) {
			System.out.println(book);
		}
	}
}
