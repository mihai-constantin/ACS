package com.mihai.libraryapp.domain;

import com.mihai.libraryapp.email.Email;
import com.mihai.libraryapp.email.EmailService;
import com.mihai.libraryapp.exceptions.ClientExistsException;
import com.mihai.libraryapp.utils.IClientRegistrationListener;

import java.text.DateFormat;
import java.util.*;

public class Library {
	
	private final Set<Client> clients = new LinkedHashSet<Client>();
	private final List<IClientRegistrationListener> listeners = new ArrayList<>();
	
	private int printedClients = 0;
	private int emailedClients = 0;
	private int debuggedClients = 0;

	private final EmailService emailService = new EmailService();

	public Library() {
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
        for (IClientRegistrationListener listener: listeners) {
            listener.onClientAdded(client);
        }
    }
	
	public Set<Client> getClients() {
		return Collections.unmodifiableSet(clients);
	}

	public Set<IBook> getBorrowedBooks() {
		Set<IBook> books = new LinkedHashSet<>();
		for (Client client : clients) {
			books.addAll(client.getBooks());
		}
		return Collections.unmodifiableSet(books);
	}

	public EmailService getEmailService() {
		return emailService;
	}
	
	class PrintClientListener implements IClientRegistrationListener {
		@Override 
		public void onClientAdded(Client client) {
	        System.out.println("[PrintClientListener] Client added: " + client.getName());
	        printedClients++;
	    }
	}
	
	class EmailNotificationListener implements IClientRegistrationListener {
		@Override 
		public void onClientAdded(Client client) {
	        emailedClients++;
			Email email = new Email(client, "Library", client.getName(), "Welcome to our library subscription!", "Enjoy every word you read!");
			emailService.sendNotificationEmail(email);
	    }
	}
	
	class DebugListener implements IClientRegistrationListener {
        @Override 
        public void onClientAdded(Client client) {
            System.out.println("[DebugListener] Client " + client.getName() + " added on: " + DateFormat.getDateInstance(DateFormat.FULL).format(new Date()));
            debuggedClients++;
        }
    }
}




