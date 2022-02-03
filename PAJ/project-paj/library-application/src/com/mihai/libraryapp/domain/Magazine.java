package com.mihai.libraryapp.domain;

import com.mihai.libraryapp.annotations.ActiveRecordEntity;

@ActiveRecordEntity(tableName = "MAGAZINE", columnKeyName = "id")
public class Magazine extends AbstractBook {
    public Magazine(int id, String title, int numberOfPages, int borrowedDays) {
        super(id, title, numberOfPages, borrowedDays);
    }

    @Override
    public String toString() {
        return "Magazine{" +
                "id=" + id +
                ", title='" + title + '\'' +
                ", numberOfPages=" + numberOfPages +
                ", borrowedDays=" + borrowedDays +
                ", available=" + available +
                '}';
    }
}
