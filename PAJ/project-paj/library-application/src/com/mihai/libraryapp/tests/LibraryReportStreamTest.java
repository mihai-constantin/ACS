package com.mihai.libraryapp.tests;

import com.mihai.libraryapp.domain.*;
import com.mihai.libraryapp.exceptions.AlreadyAvailableBookException;
import com.mihai.libraryapp.exceptions.AlreadyBorrowedBookException;
import com.mihai.libraryapp.exceptions.ClientExistsException;
import com.mihai.libraryapp.report.LibraryReportStreams;
import com.mihai.libraryapp.service.LibraryService;
import org.junit.Before;
import org.junit.Test;

import java.util.*;

import static org.junit.Assert.assertEquals;

public class LibraryReportStreamTest {

    Library library;
    LibraryReportStreams libraryReport;

    Client client1;
    Client client2;
    Client client3;

    IBook novel;
    IBook magazine;
    IBook article;

    @Before
    public void setUp() throws ClientExistsException {
        library = new Library();
        libraryReport = new LibraryReportStreams();

        client1 = new Client("Michael", Gender.MALE, "New York");
        client2 = new Client("Anna", Gender.FEMALE, "Paris");
        client3 = new Client("Emily", Gender.FEMALE, "London");

        LibraryService.addClient(library, client1);
        LibraryService.addClient(library, client2);
        LibraryService.addClient(library, client3);

        novel = new Novel(1, "Les Miserables", 852, 20, "Victor Hugo", "Penguin");
        magazine = new Magazine(2, "Vogue", 30, 5);
        article = new Article(3, "FFT", 10, 3, new HashSet<>(Arrays.asList("Huang", "Sam", "Alex")));
    }

    @Test
    public void numberOfClientsTest() {
        assertEquals(3, libraryReport.getNumberOfClients(library));
    }

    @Test
    public void numberOfBorrowedBooksTest() throws AlreadyBorrowedBookException, AlreadyAvailableBookException {
        client1.addBook(novel);
        client2.addBook(magazine);
        client2.addBook(article);

        assertEquals(3, libraryReport.getNumberOfBorrowedBooks(library));

        client2.returnBook(article);

        assertEquals(2, libraryReport.getNumberOfBorrowedBooks(library));
    }

    @Test
    public void getClientsSortedTest() throws ClientExistsException {
        ArrayList<Client> sortedArray = new ArrayList<>();
        sortedArray.add(client2);
        sortedArray.add(client3);
        sortedArray.add(client1);

        System.out.println(libraryReport.getClientsSorted(library));
        System.out.println(sortedArray);

        SortedSet<Client> sortedSet = libraryReport.getClientsSorted(library);

        assertEquals(sortedArray, new ArrayList<>(sortedSet));
    }

    @Test
    public void getBorrowedBooksSortedByName() throws AlreadyBorrowedBookException {
        client1.addBook(novel);
        client1.addBook(magazine);
        client1.addBook(article);

        SortedSet<IBook> sortedSet = libraryReport.getBorrowedBooksSortedByName(library);
        System.out.println(sortedSet);

        ArrayList<IBook> sortedArray = new ArrayList<>();
        sortedArray.add(article);
        sortedArray.add(novel);
        sortedArray.add(magazine);

        assertEquals(sortedArray, new ArrayList<>(sortedSet));
    }

    @Test
    public void getClientsByCityTest() {
        Map <String, List<Client>> expectedMap = new HashMap<>();
        expectedMap.put("New York", new ArrayList<>(List.of(client1)));
        expectedMap.put("Paris", new ArrayList<>(List.of(client2)));
        expectedMap.put("London", new ArrayList<>(List.of(client3)));

        Map<String, List<Client>> map = libraryReport.getClientsByCity(library);

        assertEquals(expectedMap, map);
    }
}
