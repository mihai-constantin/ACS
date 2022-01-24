package com.luxoft.effectivejava.module01.item05.fastversion;

import java.util.Date;
import java.util.GregorianCalendar;

public class Main {
	
	public static void main(String[] args) {
		int priviligedClients = 0;
		
		Date start = new Date();
		
		for (int i=0; i<10000000; i++) {
			Client client = new Client(generateRandomDate());
			if (client.isPrivilegedClient()) {
				priviligedClients++;
			}
		}
		
		Date end = new Date();
		
		System.out.println(priviligedClients + " priviliged clients generated within " + (end.getTime()-start.getTime()) + " miliseconds.");
		
	}
	
	private static Date generateRandomDate() {
		GregorianCalendar gregorianCalendar = new GregorianCalendar();

        int year = randBetween(2010, 2016);
        gregorianCalendar.set(GregorianCalendar.YEAR, year);
        int dayOfYear = randBetween(1, gregorianCalendar.getActualMaximum(GregorianCalendar.DAY_OF_YEAR));
        gregorianCalendar.set(GregorianCalendar.DAY_OF_YEAR, dayOfYear);
        
        return gregorianCalendar.getTime();
	}
	
	public static int randBetween(int start, int end) {
        return start + (int)Math.round(Math.random() * (end - start));
    }

}
