// Public class with exposed immutable fields - questionable
package com.luxoft.effectivejava.module03.item14;

public final class PhoneNumber {
	public final short areaCode;
	public final short prefix;
	public final short lineNumber;
	
	public PhoneNumber(int areaCode, int prefix, int lineNumber) {
		this.areaCode = (short) areaCode;
		this.prefix = (short) prefix;
		this.lineNumber = (short) lineNumber;
	}
}
