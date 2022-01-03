package com.luxoft.bankapp.domain.report;

import com.luxoft.bankapp.domain.Account;
import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.CheckingAccount;
import com.luxoft.bankapp.domain.Client;

import java.util.*;
import java.util.function.Supplier;
import java.util.stream.Collectors;

public class BankReportStreams implements IBankReport {

    public BankReportStreams() {
        System.out.println("--- Bank Report Streams---");
    }

    public int getNumberOfClients(Bank bank) {
        return bank.getClients().size();
    }

    public int getNumberOfAccounts(Bank bank) {
        return bank
                .getClients()
                .stream()
                .map(client -> client.getAccounts().size())
                .reduce(0, Integer::sum);
    }

    public SortedSet<Client> getClientsSorted(Bank bank) {
        Supplier<SortedSet<Client>> sortedSet = () -> new TreeSet<>(Comparator.comparing(Client::getName));
        return bank
                .getClients()
                .stream()
                .collect(Collectors.toCollection(sortedSet));
    }

    public double getTotalSumInAccounts(Bank bank) {
        return bank
                .getClients()
                .stream()
                .map(client -> client
                        .getAccounts()
                        .stream()
                        .map(Account::getBalance)
                        .reduce(0.0, Double::sum))
                .reduce(0.0, Double::sum);
    }

    public SortedSet<Account> getAccountsSortedBySum(Bank bank) {
        Supplier<SortedSet<Account>> sortedSet = () -> new TreeSet<>(Comparator.comparing(Account::getBalance));
        return bank
                .getClients()
                .stream()
                .map(Client::getAccounts)
                .flatMap(Collection::stream)
                .collect(Collectors.toCollection(sortedSet));
    }

    public double getBankCreditSum(Bank bank) {
        return bank
                .getClients()
                .stream()
                .map(Client::getAccounts)
                .flatMap(Collection::stream)
                .filter(account -> account instanceof CheckingAccount)
                .map(account -> ((CheckingAccount)account).getOverdraft())
                .reduce(0.0, Double::sum);
    }

    public Map<Client, Collection<Account>> getCustomerAccounts(Bank bank) {
        return bank
                .getClients()
                .stream()
                .collect(Collectors.toMap(
                        client -> client,
                        Client::getAccounts
                ));
    }

    public Map<String, List<Client>> getClientsByCity(Bank bank) {
        return bank
                .getClients()
                .stream()
                .collect(Collectors.groupingBy(Client::getCity));
    }
}
