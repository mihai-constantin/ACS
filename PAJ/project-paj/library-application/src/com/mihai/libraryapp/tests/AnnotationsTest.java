package com.mihai.libraryapp.tests;

import com.mihai.libraryapp.domain.Article;
import com.mihai.libraryapp.domain.Magazine;
import com.mihai.libraryapp.domain.Novel;
import org.junit.Test;

import java.util.Arrays;
import java.util.HashSet;

import static org.junit.Assert.assertEquals;

public class AnnotationsTest {

    @Test
    public void testAnnotationsGetById() {
        Novel novel = new Novel(1, "Les Miserables", 852, 20, "Victor Hugo", "Penguin");
        String novel_getById = novel.getById(1);
        System.out.println(novel_getById);
        assertEquals("SELECT * FROM NOVEL WHERE id=1", novel_getById);

        Magazine magazine = new Magazine(2, "Vogue", 30, 5);
        String magazine_getById = magazine.getById(2);
        System.out.println(magazine_getById);
        assertEquals("SELECT * FROM MAGAZINE WHERE id=2", magazine_getById);

        Article article = new Article(3, "FFT", 10, 3, new HashSet<>(Arrays.asList("Huang", "Sam", "Alex")));
        String article_getById = article.getById(3);
        System.out.println(article_getById);
        assertEquals("SELECT * FROM ARTICLE WHERE id=3", article_getById);
    }

    @Test
    public void testAnnotationsGetAll() {
        Novel novel = new Novel(1, "Les Miserables", 852, 20, "Victor Hugo", "Penguin");
        String novel_getAll = novel.getAll();
        System.out.println(novel_getAll);
        assertEquals("SELECT * FROM NOVEL", novel_getAll);

        Magazine magazine = new Magazine(2, "Vogue", 30, 5);
        String magazine_getAll = magazine.getAll();
        System.out.println(magazine_getAll);
        assertEquals("SELECT * FROM MAGAZINE", magazine_getAll);

        Article article = new Article(3, "FFT", 10, 3, new HashSet<>(Arrays.asList("Huang", "Sam", "Alex")));
        String article_getAll = article.getAll();
        System.out.println(article_getAll);
        assertEquals("SELECT * FROM ARTICLE", article_getAll);
    }
}
