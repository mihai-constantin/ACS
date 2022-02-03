package com.mihai.libraryapp.report;

import com.mihai.libraryapp.domain.Client;
import com.mihai.libraryapp.domain.IBook;
import com.mihai.libraryapp.domain.Library;

import java.util.*;

public class LibraryReport implements ILibraryReport {

    public LibraryReport() {
        System.out.println("--- Library Report ---");
    }

    @Override
    public int getNumberOfClients(Library library) {
        return library.getClients().size();
    }

    @Override
    public int getNumberOfBorrowedBooks(Library library) {
        int numberOfBorrowedBooks = 0;
        for (Client client : library.getClients()) {
            numberOfBorrowedBooks += client.getBooks().size();
        }
        return numberOfBorrowedBooks;
    }

    @Override
    public SortedSet<Client> getClientsSorted(Library library) {
        SortedSet<Client> sortedSet = new TreeSet<>(Comparator.comparing(Client::getName));
        sortedSet.addAll(library.getClients());
        return sortedSet;
    }

    @Override
    public SortedSet<IBook> getBorrowedBooksSortedByName(Library library) {
        SortedSet<IBook> sortedSet = new TreeSet<>(Comparator.comparing(IBook::getTitle));
        sortedSet.addAll(library.getBorrowedBooks());
        return sortedSet;
    }

    @Override
    public Map<String, List<Client>> getClientsByCity(Library library) {
        Map <String, List<Client>> map = new HashMap<>();
        for (Client client : library.getClients()) {
            String city = client.getCity();
            List<Client> clients;
            if (!map.containsKey(city)) {
                clients = new ArrayList<>();
            } else {
                clients = map.get(city);
            }
            clients.add(client);
            map.put(city, clients);
        }
        return map;
    }
}
