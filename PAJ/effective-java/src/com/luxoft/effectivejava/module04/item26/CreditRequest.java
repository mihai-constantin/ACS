package com.luxoft.effectivejava.module04.item26;

public class CreditRequest {
	private State state;
	private double creditRate;
	private double clientSalary;
	
	public CreditRequest(double creditRate, double clientSalary){ 
		state = CreditRequestState.ANALYSIS;
		this.creditRate = creditRate;
		this.clientSalary = clientSalary;
	} 
	
	public void setState(State state){ 
		this.state = state; 
	} 
	
	public State getState(){ 
		return state; 
	}
	
	public double getCreditRate() {
		return creditRate;
	}

	public void setCreditRate(double creditRate) {
		this.creditRate = creditRate;
	}

	public double getClientSalary() {
		return clientSalary;
	}

	public void setClientSalary(double clientSalary) {
		this.clientSalary = clientSalary;
	}
	
	public void doAction(){
		state.doAction(this);
	}

}
