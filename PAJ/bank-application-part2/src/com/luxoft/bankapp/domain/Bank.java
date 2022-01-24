package com.luxoft.bankapp.domain;

import java.io.Serializable;
import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import com.luxoft.bankapp.email.Email;
import com.luxoft.bankapp.email.EmailException;
import com.luxoft.bankapp.email.EmailService;
import com.luxoft.bankapp.exceptions.ClientExistsException;
import com.luxoft.bankapp.utils.ClientRegistrationListener;

public class Bank implements Serializable {
	
	private static final long serialVersionUID = -4157871135257285214L;
	private final Set<Client> clients = new HashSet<Client>();
	private final ArrayList<ClientRegistrationListener> listeners = new ArrayList<ClientRegistrationListener>();
	private EmailService emailService;

	private Client admin = new Client("Admin", Gender.MALE);
	
	private Client system = new Client("System", Gender.MALE);
	
	private int printedClients = 0;
	private int emailedClients = 0;
	private int debuggedClients = 0;
	
	public Bank() {
		listeners.add(new PrintClientListener());
		listeners.add(new EmailNotificationListener());
		listeners.add(new DebugListener());
		admin.setCity("New York");
		admin.setPhoneAreaCode("0123");
		admin.setPhoneNumber("9876543");
		
		system.setCity("Boston");
		system.setPhoneAreaCode("0121");
		system.setPhoneNumber("9875043");
		
		
	}
	
	public void setEmailService(EmailService emailService) {
		this.emailService = emailService;
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
	
	public Client getClient(String name) {
        for (Client client: clients)
            if (client.getName().equals(name))
                return client;
        return null;
    }
	
	class PrintClientListener implements ClientRegistrationListener, Serializable {
		private static final long serialVersionUID = 2777987742204604236L;

		@Override 
		public void onClientAdded(Client client) {
	        System.out.println("Client added: " + client.getName());
	    }

	}
	
	class EmailNotificationListener implements ClientRegistrationListener, Serializable {
		private static final long serialVersionUID = -2360873324733537279L;

		@Override 
		public void onClientAdded(Client client) {
	        System.out.println("Notification email for client " + client.getName() + " to be sent");
	        
	        if(emailService != null) {
		        try {
		        	emailService.sendNotificationEmail(
	                        new Email()
	                                .setFrom(system)
	                                .setTo(admin)
	                                .setCopy(client)
	                                .setTitle("Client Added Notification")
	                                .setBody("Client added: " + client)
	                );
	            } catch (EmailException e) {
	                System.err.println(e.getMessage());
	            }
	        }
	    }
	}
	
	class DebugListener implements ClientRegistrationListener, Serializable {
		private static final long serialVersionUID = -7600469994081192859L;

		@Override public void onClientAdded(Client client) {
            System.out.println("Client " + client.getName() + " added on: " + DateFormat.getDateInstance(DateFormat.FULL).format(new Date()));
        }
    }

}




