package com.luxoft.bankapp.domain;

import java.text.DateFormat;
import java.util.*;

import com.luxoft.bankapp.email.Email;
import com.luxoft.bankapp.email.EmailService;
import com.luxoft.bankapp.exceptions.ClientExistsException;
import com.luxoft.bankapp.utils.ClientRegistrationListener;

public class Bank {
	
	private final Set<Client> clients = new LinkedHashSet<Client>();
	private final List<ClientRegistrationListener> listeners = new ArrayList<ClientRegistrationListener>();
	
	private int printedClients = 0;
	private int emailedClients = 0;
	private int debuggedClients = 0;

	private final EmailService emailService = new EmailService();

	public Bank() {
		listeners.add(new PrintClientListener());
		listeners.add(new EmailNotificationListener());
		listeners.add(new DebugListener());
	}
	
	public int getPrintedClients() {
		return printedClients;
	}

	public int getEmailedClients() {
		return emailedClients;
	}

	public int getDebuggedClients() {
		return debuggedClients;
	}
	
	public void addClient(final Client client) throws ClientExistsException {
    	if (clients.contains(client)) {
    		throw new ClientExistsException("Client already exists into the bank");
    	} 
    		
    	clients.add(client);
        notify(client);
	}
	
	private void notify(Client client) {
        for (ClientRegistrationListener listener: listeners) {
            listener.onClientAdded(client);
        }
    }
	
	public Set<Client> getClients() {
		return Collections.unmodifiableSet(clients);
	}

	public EmailService getEmailService() {
		return emailService;
	}
	
	class PrintClientListener implements ClientRegistrationListener {
		@Override 
		public void onClientAdded(Client client) {
	        System.out.println("Client added: " + client.getName());
	        printedClients++;
	    }
	}
	
	class EmailNotificationListener implements ClientRegistrationListener {
		@Override 
		public void onClientAdded(Client client) {
	        System.out.println("Notification email for client " + client.getName() + " to be sent");
	        emailedClients++;
			Email email = new Email(client, "FROM", "TO", "SUBJECT", "BODY!");
			emailService.sendNotificationEmail(email);
	    }
	}
	
	class DebugListener implements ClientRegistrationListener {
        @Override 
        public void onClientAdded(Client client) {
            System.out.println("Client " + client.getName() + " added on: " + DateFormat.getDateInstance(DateFormat.FULL).format(new Date()));
            debuggedClients++;
        }
    }
}




