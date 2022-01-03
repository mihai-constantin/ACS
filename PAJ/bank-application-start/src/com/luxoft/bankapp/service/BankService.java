package com.luxoft.bankapp.service;

import com.luxoft.bankapp.domain.Account;
import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.exceptions.ClientExistsException;

public class BankService {
	
	public static void addClient(Bank bank, Client client) throws ClientExistsException {
        bank.addClient(client);
    }
	
	public static void printMaximumAmountToWithdraw(Bank bank) {
		System.out.format("%nPrint maximum amount to withdraw for all clients%n");
		
        StringBuilder result = new StringBuilder();
        for (Client client: bank.getClients()) {
            result.append("Client: ")
                  .append(client)
                  .append("\n");
            int i = 1;
            for (Account account: client.getAccounts()) {
                result.append("Account nr. ")
                      .append(i++)
                      .append(", maximum amount to withdraw: ")
                      .append(Math.round(account.maximumAmountToWithdraw() * 100) / 100d)
                      .append("\n");
            }
        }

        System.out.println(result.toString());
    }
	
}
