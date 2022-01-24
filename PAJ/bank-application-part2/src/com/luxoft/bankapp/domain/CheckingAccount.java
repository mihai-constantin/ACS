package com.luxoft.bankapp.domain;

import java.util.Formatter;
import java.util.Locale;

import com.luxoft.bankapp.exceptions.NotEnoughFundsException;
import com.luxoft.bankapp.exceptions.OverdraftLimitExceededException;
import com.luxoft.bankapp.utils.Params;

public class CheckingAccount extends AbstractAccount {
	
	private static final long serialVersionUID = 7922392307762434334L;
	public double overdraft;
	private Currency currency;

	public CheckingAccount(int id, double amount, double overdraft) {
		super(id, amount);
		if (overdraft < 0) {
			throw new IllegalArgumentException("Cannot create an account with a starting negative overdraft");
		}
		this.overdraft = overdraft;
		this.setType(AbstractAccount.CHECKING_ACCOUNT_TYPE);
	}
	
	public CheckingAccount(int id, double amount, double overdraft, Currency currency) {
		super(id, amount);
		if (overdraft < 0) {
			throw new IllegalArgumentException("Cannot create an account with a starting negative overdraft");
		}
		this.overdraft = overdraft;
		this.currency = currency;
		this.setType(AbstractAccount.CHECKING_ACCOUNT_TYPE);
	}
	
	public Currency getCurrency() {
		return currency;
	}
	
	@Override
    public void withdraw(double value) throws OverdraftLimitExceededException {
        try {
            super.withdraw(value);
        } catch (NotEnoughFundsException notEnoughFundsException) {
            throw new OverdraftLimitExceededException(notEnoughFundsException, overdraft);
        }
    }

	@Override
	public String toString() {
		Formatter fmt = new Formatter(Locale.US);
		String stringAccount = fmt.format("Checking account %d, balance: %.2f, overdraft: %.2f", getId(), balance, overdraft).toString(); 
		fmt.close();
		return stringAccount;
	}
	
	public static Account parse(Params params) {
		String id = params.get("id");
		String balance = params.get("balance");
		String overdraft = params.get("overdraft");
		String currency = params.get("currency");
        return new CheckingAccount(
        		Integer.parseInt(id), 
                Double.parseDouble(balance),
                Double.parseDouble(overdraft),
                new Currency(currency));
    }
}
