package com.luxoft.effectivejava.module01.item05.slowversion;

import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

public class Client {
	private final Date becomeClientDate;

	public Client(Date becomeClientDate) {
		this.becomeClientDate = new Date(becomeClientDate.getTime());
	}

	// Other fields, methods omitted

	// DON'T DO THIS!
	public boolean isPrivilegedClient() {
		// Unnecessary allocation of expensive object
		Calendar gmtCalendar = Calendar.getInstance(TimeZone.getTimeZone("GMT"));
		gmtCalendar.set(2010, Calendar.JANUARY, 1, 0, 0, 0);
		Date promotionStart = gmtCalendar.getTime();
		gmtCalendar.set(2011, Calendar.JANUARY, 1, 0, 0, 0);
		Date promotionEnd = gmtCalendar.getTime();
		return becomeClientDate.compareTo(promotionStart) >= 0 && 
			   becomeClientDate.compareTo(promotionEnd) < 0;
	}


}
