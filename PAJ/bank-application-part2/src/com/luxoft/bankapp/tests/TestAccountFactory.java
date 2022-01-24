package com.luxoft.bankapp.tests;

import com.luxoft.bankapp.domain.AbstractAccount;
import com.luxoft.bankapp.factory.AccountFactory;
import com.luxoft.bankapp.factory.AccountType;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class TestAccountFactory {

    @Test
    public void testCheckingAccount() {
        AbstractAccount account = AccountFactory.newAccount(AccountType.CHECKING, 1, 100);
        assertEquals("CheckingAccount", account.getClass().getSimpleName());
    }

    @Test
    public void testSavingAccount() {
        AbstractAccount account = AccountFactory.newAccount(AccountType.SAVING, 1, 100);
        assertEquals("SavingAccount", account.getClass().getSimpleName());
    }
}
