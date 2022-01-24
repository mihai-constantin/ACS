package com.luxoft.effectivejava.module01.item05.fastversion;

import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

public class Client {
	private final Date becomeClientDate;

	public Client(Date becomeClientDate) {
		this.becomeClientDate = new Date(becomeClientDate.getTime());
	}

	// Other fields, methods

	/**
	 * The starting and ending dates of the promotion period.
	 */
	private static final Date PROMOTION_START;
	private static final Date PROMOTION_END;

	static {
		Calendar gmtCal = Calendar.getInstance(TimeZone.getTimeZone("GMT"));
		gmtCal.set(2010, Calendar.JANUARY, 1, 0, 0, 0);
		PROMOTION_START = gmtCal.getTime();
		gmtCal.set(2011, Calendar.JANUARY, 1, 0, 0, 0);
		PROMOTION_END = gmtCal.getTime();
	}

	public boolean isPrivilegedClient() {
		return becomeClientDate.compareTo(PROMOTION_START) >= 0 && 
			   becomeClientDate.compareTo(PROMOTION_END) < 0;
	}
}
