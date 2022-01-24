package com.luxoft.bankapp.email;

public class EmailException extends Exception {
	private static final long serialVersionUID = 3523913455438905283L;

	public EmailException(String message){
        super(message);
    }
}
