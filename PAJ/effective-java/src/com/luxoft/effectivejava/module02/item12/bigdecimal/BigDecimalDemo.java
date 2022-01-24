package com.luxoft.effectivejava.module02.item12.bigdecimal;

import java.math.BigDecimal;

public class BigDecimalDemo {

	public static void main(String[] args) {
		BigDecimal bigDecimal1, bigDecimal2;

		bigDecimal1 = new BigDecimal("10.0");
		bigDecimal2 = new BigDecimal("10.00");

		System.out.println(bigDecimal1.compareTo(bigDecimal2)); 
		System.out.println(bigDecimal1.equals(bigDecimal2));

	}
}
