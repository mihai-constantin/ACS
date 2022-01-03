package com.luxoft.bankapp.tests;

import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.SavingAccount;
import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class Test6 {

    @Test
    public void testAnnotations() {
        SavingAccount savingAccount = new SavingAccount(1, 100);
        CheckingAccount checkingAccount = new CheckingAccount(2, 1000.0, 100.0);

        String savingAccount_getById = savingAccount.getById(1);
        System.out.println(savingAccount_getById);
        assertEquals("SELECT * FROM SAVING_ACCOUNT WHERE id=1", savingAccount_getById);

        String checkingAccount_getById = checkingAccount.getById(2);
        System.out.println(checkingAccount_getById);
        assertEquals("SELECT * FROM CHECKING_ACCOUNT WHERE id=2", checkingAccount_getById);

        String savingAccount_getAll = savingAccount.getAll();
        System.out.println(savingAccount_getAll);
        assertEquals("SELECT * FROM SAVING_ACCOUNT", savingAccount_getAll);

        String checkingAccount_getAll = checkingAccount.getAll();
        System.out.println(checkingAccount_getAll);
        assertEquals("SELECT * FROM CHECKING_ACCOUNT", checkingAccount_getAll);
    }
}
