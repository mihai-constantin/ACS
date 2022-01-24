// Tagged class - vastly inferior to a class hierarchy!
package com.luxoft.effectivejava.module03.item18.taggedclass;

public class Account {
	enum AccountType {
		SAVING_ACCOUNT, CHECKING_ACCOUNT
	};

	// Tag field - the type of this account
	private final AccountType accountType;

	// This field is used for all accounts
	private double balance;

	// This field is used only if account type is checking
	private double overdraft;

	// Constructor for saving account
	public Account(double balance) {
		accountType = AccountType.SAVING_ACCOUNT;
		this.balance = balance;
	}

	// Constructor for checking account
	public Account(double balance, double overdraft) {
		accountType = AccountType.CHECKING_ACCOUNT;
		this.balance = balance;
		this.overdraft = overdraft;
	}

	public double maximumAmountToWithdraw(){
		switch (accountType) {
		case SAVING_ACCOUNT:
			return balance;
		case CHECKING_ACCOUNT:
			return balance + overdraft;
		default:
			throw new AssertionError();
		}
    }
}
