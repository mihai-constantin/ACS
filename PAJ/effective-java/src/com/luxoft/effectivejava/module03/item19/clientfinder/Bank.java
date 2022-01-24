package com.luxoft.effectivejava.module03.item19.clientfinder;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class Bank {

	private Set<Client> clients = new HashSet<>();

    public Set<Client> getClients(){
        return Collections.unmodifiableSet(clients);
    }

    public void addClient(Client client) {
    	if (!clients.contains(client)) {
    		clients.add(client);
    	}
    }
    
}