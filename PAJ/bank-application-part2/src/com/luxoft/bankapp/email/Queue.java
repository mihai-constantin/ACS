package com.luxoft.bankapp.email;

import java.io.Serializable;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Queue implements Serializable {

	private static final long serialVersionUID = -367534955230149744L;
	
	private List<Email> emails = Collections.synchronizedList(new LinkedList<Email>());
	
    public void add(Email email) {
        emails.add(email);
    }

    public Email get() {
        if (emails.size() > 0) {
            return emails.remove(emails.size() - 1);
        } 
        
        return null;
    }
    
}
