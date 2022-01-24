package com.luxoft.bankapp.factory;

import com.luxoft.bankapp.domain.AbstractAccount;
import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.SavingAccount;

public class AccountFactory {

    public static AbstractAccount newAccount(AccountType accountType, int id, double amount) {
        if (accountType == null) {
            return null;
        }

        return switch (accountType) {
            case SAVING -> new SavingAccount(id, amount);
            case CHECKING -> new CheckingAccount(id, amount, 0);
        };
    }
}
