package com.mihai.libraryapp.domain;

public interface IBook {
    int getId();
    String getTitle();
    boolean isAvailable();
    void setAvailable(boolean available);
}
