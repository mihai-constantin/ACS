package com.luxoft.effectivejava.module02.item12;

import java.util.Collections;
import java.util.Set;
import java.util.TreeSet;

public class WordList {
	public static void main(String[] args) {
		Set<String> s = new TreeSet<String>();
		Collections.addAll(s, args);
		System.out.println(s);
	}
}
