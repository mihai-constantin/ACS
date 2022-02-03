package com.mihai.libraryapp.report;

import com.mihai.libraryapp.domain.Client;
import com.mihai.libraryapp.domain.IBook;
import com.mihai.libraryapp.domain.Library;

import java.util.List;
import java.util.Map;
import java.util.SortedSet;

public interface ILibraryReport {

    int getNumberOfClients(Library library);
    int getNumberOfBorrowedBooks(Library library);
    SortedSet<Client> getClientsSorted(Library library);
    SortedSet<IBook> getBorrowedBooksSortedByName(Library library);
    Map<String, List<Client>> getClientsByCity(Library library);
}
