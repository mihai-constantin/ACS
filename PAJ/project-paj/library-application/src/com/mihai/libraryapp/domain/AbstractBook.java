package com.mihai.libraryapp.domain;

import com.mihai.libraryapp.annotations.ActiveRecord;

public abstract class AbstractBook extends ActiveRecord implements IBook {

    final int id;
    protected final String title;
    protected final int numberOfPages;
    protected int borrowedDays;
    protected boolean available;

    public AbstractBook(int id, String title, int numberOfPages, int borrowedDays) {
        this.id = id;
        this.title = title;
        this.numberOfPages = numberOfPages;
        this.borrowedDays = borrowedDays;
        this.available = true;
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public String getTitle() {
        return title;
    }

    public int getNumberOfPages() {
        return numberOfPages;
    }

    @Override
    public boolean isAvailable() {
        return available;
    }

    @Override
    public void setAvailable(boolean available) {
        this.available = available;
    }
}
