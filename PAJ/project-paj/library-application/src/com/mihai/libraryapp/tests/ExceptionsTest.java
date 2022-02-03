package com.mihai.libraryapp.tests;

import com.mihai.libraryapp.domain.*;
import com.mihai.libraryapp.exceptions.AlreadyAvailableBookException;
import com.mihai.libraryapp.exceptions.AlreadyBorrowedBookException;
import com.mihai.libraryapp.exceptions.ClientExistsException;
import com.mihai.libraryapp.service.LibraryService;
import org.junit.Test;

public class ExceptionsTest {

    @Test(expected = ClientExistsException.class)
    public void testAddClient() throws ClientExistsException {
        Library library = new Library();
        Client client = new Client("Michael", Gender.MALE);

        LibraryService.addClient(library, client);

        // trying to add the same client to the library
        LibraryService.addClient(library, client);
    }

    @Test(expected = AlreadyBorrowedBookException.class)
    public void testBorrowedBook() throws ClientExistsException, AlreadyBorrowedBookException {
        Library library = new Library();
        Client client1 = new Client("Michael", Gender.MALE);
        Client client2 = new Client("Anna", Gender.FEMALE);

        LibraryService.addClient(library, client1);
        LibraryService.addClient(library, client2);

        IBook novel = new Novel(1, "Les Miserables", 852, 20, "Victor Hugo", "Penguin");

        client1.addBook(novel);

        // trying to borrow an unavailable book
        client2.addBook(novel);
    }

    @Test(expected = AlreadyAvailableBookException.class)
    public void test() throws ClientExistsException, AlreadyAvailableBookException {
        Library library = new Library();
        Client client = new Client("Michael", Gender.MALE);
        LibraryService.addClient(library, client);

        IBook novel = new Novel(1, "Les Miserables", 852, 20, "Victor Hugo", "Penguin");

        client.returnBook(novel);
    }
}
