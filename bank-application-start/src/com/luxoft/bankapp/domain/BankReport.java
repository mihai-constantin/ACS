package com.luxoft.bankapp.domain;

import java.util.*;

public class BankReport {

    public int getNumberOfClients(Bank bank) {
        return bank.getClients().size();
    }

    public int getNumberOfAccounts(Bank bank) {
        int numberOfAccounts = 0;
        for (Client client : bank.getClients()) {
            numberOfAccounts += client.getAccounts().size();
        }
        return numberOfAccounts;
    }

    public SortedSet<Client> getClientsSorted(Bank bank) {
        SortedSet<Client> sortedSet = new TreeSet<>(Comparator.comparing(Client::getName));
        sortedSet.addAll(bank.getClients());
        return sortedSet;
    }

    public double getTotalSumInAccounts(Bank bank) {
        double totalSum = 0;
        for (Client client : bank.getClients()) {
            for (Account account : client.getAccounts()) {
                totalSum += account.getBalance();
            }
        }
        return totalSum;
    }

    public SortedSet<Account> getAccountsSortedBySum(Bank bank) {
        SortedSet<Account> sortedSet = new TreeSet<>(Comparator.comparing(Account::getBalance));
        for (Client client : bank.getClients()) {
            sortedSet.addAll(client.getAccounts());
        }
        return sortedSet;
    }

    public double getBankCreditSum(Bank bank) {
        double bankCreditSum = 0;
        for (Client client : bank.getClients()) {
            for (Account account : client.getAccounts()) {
                if (account instanceof CheckingAccount) {
                    bankCreditSum += ((CheckingAccount) account).getOverdraft();
                }
            }
        }
        return bankCreditSum;
    }

    public Map<Client, Collection<Account>> getCustomerAccounts(Bank bank) {
        Map<Client, Collection<Account>> map = new HashMap<>();
        for (Client client : bank.getClients()) {
            map.put(client, client.getAccounts());
        }
        return map;
    }

    public Map<String, List<Client>> getClientsByCity(Bank bank) {
        Map <String, List<Client>> map = new HashMap<>();
        for (Client client : bank.getClients()) {
            String city  = client.getCity();
            List<Client> clients;
            if (!map.containsKey(city)) {
                clients = new ArrayList<>();
            } else {
                clients = map.get(city);
            }
            clients.add(client);
            map.put(city, clients);
        }
        return map;
    }

    public void printReport(Bank bank) {
        System.out.println("--- Bank Report ---");
        System.out.println("numberOfClients: " + getNumberOfClients(bank));
        System.out.println("numberOfAccounts: " + getNumberOfAccounts(bank));
        System.out.println("clientsSorted: " + getClientsSorted(bank));
        System.out.println("totalSumInAccounts: " + getTotalSumInAccounts(bank));
        System.out.println("accountsSortedBySum: " + getAccountsSortedBySum(bank));
        System.out.println("bankCreditSum: " + getBankCreditSum(bank));
        System.out.println("customerAccounts: " + getCustomerAccounts(bank));
        System.out.println("clientsByCity: " + getClientsByCity(bank));
    }

}
