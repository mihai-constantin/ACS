package com.luxoft.bankapp.tests;

import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.SavingAccount;
import org.junit.Test;

import static org.junit.Assert.*;

public class TestCloneable {

    @Test
    public void testSavingAccount() throws CloneNotSupportedException {
        SavingAccount savingAccount = new SavingAccount(1, 100);
        SavingAccount savingAccountClone = (SavingAccount) savingAccount.clone();

        savingAccountClone.setBalance(200);

        assertSame(savingAccount.getId(), savingAccountClone.getId());
        assertNotSame(savingAccount.getBalance(), savingAccountClone.getBalance());
        assertSame(savingAccount.getCurrency(), savingAccountClone.getCurrency());
    }

    @Test
    public void testCheckingAccount() throws CloneNotSupportedException {
        CheckingAccount checkingAccount = new CheckingAccount(1, 100, 10);
        CheckingAccount checkingAccountClone = (CheckingAccount) checkingAccount.clone();

        checkingAccountClone.setBalance(200);
        checkingAccountClone.setOverdraft(50);

        assertSame(checkingAccount.getId(), checkingAccountClone.getId());
        assertNotSame(checkingAccount.getBalance(), checkingAccountClone.getBalance());
        assertNotSame(checkingAccount.getOverdraft(), checkingAccountClone.getOverdraft());
        assertSame(checkingAccount.getCurrency(), checkingAccountClone.getCurrency());
    }

}
