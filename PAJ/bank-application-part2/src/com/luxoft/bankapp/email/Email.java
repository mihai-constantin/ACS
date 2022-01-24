package com.luxoft.bankapp.email;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

import com.luxoft.bankapp.domain.Client;

public class Email implements Serializable {

	private static final long serialVersionUID = -3686472195559526951L;
	private Client from;
    private ArrayList<Client> to, copy;
    private String title, body;

    public Client getFrom() {
        return from;
    }

    public Email setFrom(Client from) {
        this.from = from;
        return this;
    }

    public ArrayList<Client> getTo() {
        return to;
    }

    public Email setTo(ArrayList<Client> to) {
        this.to = to;
        return this;
    }

    public Email setTo(Client to) {
    	ArrayList<Client> toList = new ArrayList<Client>();
    	toList.add(to);
        setTo(toList);
        return this;
    }

    public ArrayList<Client> getCopy() {
        return copy;
    }

    public Email setCopy(ArrayList<Client> copy) {
        this.copy = copy;
        return this;
    }

    public Email setCopy(Client copy) {
    	ArrayList<Client> copyList = new ArrayList<Client>();
    	copyList.add(copy);
        setCopy(copyList);
        return this;
    }

    public String getTitle() {
        return title;
    }

    public Email setTitle(String title) {
        this.title = title;
        return this;
    }

    public String getBody() {
        return body;
    }

    public Email setBody(String body) {
        this.body = body;
        return this;
    }
    
    @Override
    public String toString() {
    	ArrayList<Client> clients = getTo();
    	StringBuilder clientsTo = new StringBuilder();
    	for (Client c: clients) {
    		clientsTo.append(c);
    	}
    	
    	clients = getCopy();
    	StringBuilder clientsCopy = new StringBuilder();
    	for (Client c: clients) {
    		clientsCopy.append(c);
    	}
    	
    	return "SEND EMAIL:" + "\n" + 
    			"From: " + getFrom() +
    			"To: " + clientsTo +
    			"Copy: " + clientsCopy +
    			"Title: " + getTitle() + "\n" +
    			"Body: " + getBody() + "\n";
    }
}