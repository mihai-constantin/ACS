package com.luxoft.bankapp.domain.report;

import com.luxoft.bankapp.domain.Account;
import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.Client;

import java.util.*;

public interface IBankReport {

    int getNumberOfClients(Bank bank);

    int getNumberOfAccounts(Bank bank);

    SortedSet<Client> getClientsSorted(Bank bank);

    double getTotalSumInAccounts(Bank bank);

    SortedSet<Account> getAccountsSortedBySum(Bank bank);

    double getBankCreditSum(Bank bank);

    Map<Client, Collection<Account>> getCustomerAccounts(Bank bank);

    Map<String, List<Client>> getClientsByCity(Bank bank);
}
