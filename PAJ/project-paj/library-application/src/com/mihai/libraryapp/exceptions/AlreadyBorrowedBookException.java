package com.mihai.libraryapp.exceptions;

public class AlreadyBorrowedBookException extends LibraryException {
    public AlreadyBorrowedBookException(String message) {
        super(message);
    }
}
