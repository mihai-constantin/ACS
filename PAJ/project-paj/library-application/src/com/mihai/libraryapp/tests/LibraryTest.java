package com.mihai.libraryapp.tests;

import com.mihai.libraryapp.domain.*;
import com.mihai.libraryapp.exceptions.AlreadyAvailableBookException;
import com.mihai.libraryapp.exceptions.AlreadyBorrowedBookException;
import com.mihai.libraryapp.exceptions.ClientExistsException;
import com.mihai.libraryapp.service.LibraryService;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class LibraryTest {

    @Test
    public void testClient() throws ClientExistsException {
        Library library = new Library();

        Client client1 = new Client("Michael", Gender.MALE);
        Client client2 = new Client("Anna", Gender.FEMALE);

        LibraryService.addClient(library, client1);
        LibraryService.addClient(library, client2);

        assertEquals(2, library.getClients().size());
    }

    @Test
    public void testBorrowedBooks() throws AlreadyBorrowedBookException {
        Client client = new Client("Michael", Gender.MALE);
        client.addBook(new Novel(1, "War and Peace", 570, 5, "Lev Tolstoi", "Arthur"));
        client.addBook(new Novel(2, "Anna Karenina", 602, 5, "Lev Tolstoi", "Penguin"));
        assertEquals(2, client.getBooks().size());
    }

    @Test
    public void testReturnBook() throws AlreadyBorrowedBookException, ClientExistsException, AlreadyAvailableBookException {
        Library library = new Library();
        Client client = new Client("Michael", Gender.MALE);
        LibraryService.addClient(library, client);
        IBook novel1 = new Novel(1, "War and Peace", 570, 5, "Lev Tolstoi", "Arthur");
        IBook novel2 = new Novel(2, "Anna Karenina", 602, 5, "Lev Tolstoi", "Penguin");
        client.addBook(novel1);
        client.addBook(novel2);
        assertEquals(2, library.getBorrowedBooks().size());

        client.returnBook(novel2);
        assertEquals(1, library.getBorrowedBooks().size());
    }

}
