package com.luxoft.bankapp.domain;

import com.luxoft.bankapp.exceptions.NotEnoughFundsException;
import com.luxoft.bankapp.exceptions.OverdraftLimitExceededException;

public class CheckingAccount extends AbstractAccount {
	
	private double overdraft;

	public CheckingAccount(int id, double balance, double overdraft) {
		super(id, balance);
		if (overdraft < 0) {
			throw new IllegalArgumentException("Cannot create an account with a starting negative overdraft");
		}
		this.overdraft = overdraft;
	}
	
	@Override
    public void withdraw(double value) throws OverdraftLimitExceededException{
        try {
            super.withdraw(value);
        } catch (NotEnoughFundsException notEnoughFundsException) {
            throw new OverdraftLimitExceededException(notEnoughFundsException, overdraft);
        }
    }

	public double getOverdraft() {
		return overdraft;
	}
	
	public double maximumAmountToWithdraw(){
        return getBalance() + overdraft;
    }

	@Override
	public String toString() {
		return "CheckingAccount{" +
				"balance=" + balance +
				", overdraft=" + overdraft +
				'}';
	}
}
