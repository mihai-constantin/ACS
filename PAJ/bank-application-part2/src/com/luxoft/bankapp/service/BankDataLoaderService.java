package com.luxoft.bankapp.service;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;

import com.luxoft.bankapp.domain.Bank;
import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.exceptions.ClientExistsException;

public class BankDataLoaderService {
	private Bank bank;
	
    public BankDataLoaderService(Bank bank) {
		this.bank = bank;
	}

	public void readClients(String fileName) {
    	if (fileName == null) { 
    		return;
    	}
    	
        try {
        	LineNumberReader lineNumberReader = 
        			new LineNumberReader(
        					new BufferedReader(
        							new FileReader(fileName)));
            String line;
            while ((line = lineNumberReader.readLine()) != null) {
                addClient(Client.parseClient(line));
            }
            
            lineNumberReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

	private void addClient(Client client) {
		try {
			BankService.addClient(bank, client);
		} catch (ClientExistsException e) {
			e.printStackTrace();
		}
	}

}
