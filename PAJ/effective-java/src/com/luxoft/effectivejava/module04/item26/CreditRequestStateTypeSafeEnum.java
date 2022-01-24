package com.luxoft.effectivejava.module04.item26;

public class CreditRequestStateTypeSafeEnum {
	private final String state;
	
	public static final CreditRequestStateTypeSafeEnum ANALYSIS = new CreditRequestStateTypeSafeEnum("Analysis");
	public static final CreditRequestStateTypeSafeEnum ACCEPTED = new CreditRequestStateTypeSafeEnum("Accepted");
	public static final CreditRequestStateTypeSafeEnum REJECTED = new CreditRequestStateTypeSafeEnum("Rejected");
	
	public CreditRequestStateTypeSafeEnum(String state) {
		this.state = state;
	}

	public String getState() {
		return state;
	}

}
