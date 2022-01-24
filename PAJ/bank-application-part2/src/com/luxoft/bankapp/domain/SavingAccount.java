package com.luxoft.bankapp.domain;

import java.util.Formatter;
import java.util.Locale;

import com.luxoft.bankapp.utils.Params;


public class SavingAccount extends AbstractAccount {

	private static final long serialVersionUID = 9200460687227050240L;
	private Currency currency;

	public SavingAccount(int id, double amount) {
		super(id, amount);
		this.setType(AbstractAccount.SAVING_ACCOUNT_TYPE);
	}
	
	public SavingAccount(int id, double amount, Currency currency) {
		super(id, amount);
		this.currency = currency;
		this.setType(AbstractAccount.SAVING_ACCOUNT_TYPE);
	}
	
	public Currency getCurrency() {
		return currency;
	}
	
	@Override
	public String toString() {
		Formatter fmt = new Formatter(Locale.US);
		String stringAccount = fmt.format("Saving account %d, balance: %.2f", getId(), balance).toString(); 
		fmt.close();
		return stringAccount;
	}
	
	public static Account parse(Params params) {
		String id = params.get("id");
		String balance = params.get("balance");
		String currency = params.get("currency");
		
        return new SavingAccount(
        		Integer.parseInt(id), 
        		Double.parseDouble(balance),
        		new Currency(currency));
    }
	
}
