package com.luxoft.effectivejava.module01.item03.finalfield;

import java.io.ObjectStreamException;
import java.io.Serializable;

//Singleton with public final field
public class Bank implements Serializable {
	private static final long serialVersionUID = 5196879855729969483L;
	
	public static final Bank INSTANCE = new Bank();
	private Bank() { 
		
	}
	
	// readResolve method to preserve singleton property
	private Object readResolve() throws ObjectStreamException {
		// Return the one true Bank and let the GC
		// take care of the impersonator Bank.
		return INSTANCE;
	}


}

