package com.mihai.libraryapp.service;

import com.mihai.libraryapp.domain.Client;
import com.mihai.libraryapp.domain.Library;
import com.mihai.libraryapp.exceptions.ClientExistsException;

public class LibraryService {

    public static void addClient(Library library, Client client) throws ClientExistsException {
        library.addClient(client);
    }
}
