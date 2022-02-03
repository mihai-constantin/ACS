package com.mihai.libraryapp.domain;

import com.mihai.libraryapp.annotations.ActiveRecordEntity;

import java.util.Collections;
import java.util.Set;

@ActiveRecordEntity(tableName = "ARTICLE", columnKeyName = "id")
public class Article extends AbstractBook {

    private final Set<String> authors;

    public Article(int id, String title, int numberOfPages, int borrowedDays, Set<String> authors) {
        super(id, title, numberOfPages, borrowedDays);
        this.authors = authors;
    }

    public Set<String> getAuthors() {
        return Collections.unmodifiableSet(authors);
    }

    @Override
    public String toString() {
        return "Article{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", numberOfPages=" + numberOfPages +
                ", borrowedDays=" + borrowedDays +
                ", available=" + available +
                ", authors=" + authors +
                '}';
    }
}
