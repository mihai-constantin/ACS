package com.mihai.libraryapp.exceptions;

public class AlreadyAvailableBookException extends LibraryException {
    public AlreadyAvailableBookException(String message) {
        super(message);
    }
}
