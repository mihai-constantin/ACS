package com.mihai.libraryapp.report;

import com.mihai.libraryapp.domain.Client;
import com.mihai.libraryapp.domain.IBook;
import com.mihai.libraryapp.domain.Library;

import java.util.*;
import java.util.function.Supplier;
import java.util.stream.Collectors;

public class LibraryReportStreams implements ILibraryReport {

    public LibraryReportStreams() {
        System.out.println("--- Library Report Streams ---");
    }

    @Override
    public int getNumberOfClients(Library library) {
        return library.getClients().size();
    }

    @Override
    public int getNumberOfBorrowedBooks(Library library) {
        return library
                .getClients()
                .stream()
                .map(client -> client.getBooks().size())
                .reduce(0, Integer::sum);
    }

    @Override
    public SortedSet<Client> getClientsSorted(Library library) {
        Supplier<SortedSet<Client>> sortedSet = () -> new TreeSet<>(Comparator.comparing(Client::getName));
        return library
                .getClients()
                .stream()
                .collect(Collectors.toCollection(sortedSet));
    }

    @Override
    public SortedSet<IBook> getBorrowedBooksSortedByName(Library library) {
        Supplier<SortedSet<IBook>> sortedSet = () -> new TreeSet<>(Comparator.comparing(IBook::getTitle));
        return library
                .getClients()
                .stream()
                .flatMap(client -> client.getBooks().stream())
                .collect(Collectors.toCollection(sortedSet));
    }

    @Override
    public Map<String, List<Client>> getClientsByCity(Library library) {
        return library
                .getClients()
                .stream()
                .collect(Collectors.groupingBy(Client::getCity));
    }
}
