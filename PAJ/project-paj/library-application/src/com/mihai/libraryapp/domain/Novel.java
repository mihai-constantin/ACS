package com.mihai.libraryapp.domain;

import com.mihai.libraryapp.annotations.ActiveRecordEntity;

@ActiveRecordEntity(tableName = "NOVEL", columnKeyName = "id")
public class Novel extends AbstractBook {

    private final String author;
    private final String publisher;

    public Novel(int id, String title, int numberOfPages, int borrowedDays, String author, String publisher) {
        super(id, title, numberOfPages, borrowedDays);
        this.author = author;
        this.publisher = publisher;
    }

    public String getAuthor() {
        return author;
    }

    public String getPublisher() {
        return publisher;
    }

    @Override
    public String toString() {
        return "Novel{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", numberOfPages=" + numberOfPages +
                ", borrowedDays=" + borrowedDays +
                ", available=" + available +
                ", author='" + author + '\'' +
                ", publisher='" + publisher + '\'' +
                '}';
    }
}
