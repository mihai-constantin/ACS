package com.mihai.libraryapp.domain;

import com.mihai.libraryapp.exceptions.AlreadyAvailableBookException;
import com.mihai.libraryapp.exceptions.AlreadyBorrowedBookException;

import java.util.Collections;
import java.util.LinkedHashSet;
import java.util.Objects;
import java.util.Set;

public class Client {

    private String name;
    private Gender gender;
    private String city;
    private Set<IBook> books = new LinkedHashSet<>();

    public Client(String name, Gender gender) {
        this.name = name;
        this.gender = gender;
    }

    public Client(String name, Gender gender, String city) {
        this.name = name;
        this.gender = gender;
        this.city = city;
    }

    public void addBook(final IBook book) throws AlreadyBorrowedBookException {
        if (!book.isAvailable()) {
            throw  new AlreadyBorrowedBookException("cannot borrow book with id " + book.getId() + " because it's already borrowed!");
        }
        books.add(book);
        book.setAvailable(false);
    }

    public void returnBook(final IBook book) throws AlreadyAvailableBookException {
        if (book.isAvailable()) {
            throw new AlreadyAvailableBookException("book with id " + book.getId() + " is already available");
        }
        books.remove(book);
        book.setAvailable(true);
    }

    public String getName() {
        return name;
    }

    public Gender getGender() {
        return gender;
    }

    public String getCity() {
        return city;
    }

    public Set<IBook> getBooks() {
        return Collections.unmodifiableSet(books);
    }

    public String getClientGreeting() {
       return name;
    }

    @Override
    public String toString() {
        return getClientGreeting();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Client client = (Client) o;
        return Objects.equals(name, client.name) && gender == client.gender;
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, gender);
    }
}
