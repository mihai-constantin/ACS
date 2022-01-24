package com.luxoft.effectivejava.module04.item26;

//Emulated extensible enum using an interface
public interface State {
	void doAction(CreditRequest creditRequest);
}
