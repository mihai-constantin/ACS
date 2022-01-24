package com.luxoft.effectivejava.module04.item26;

public enum CreditRequestState implements State {
	ANALYSIS  {
		public void doAction(CreditRequest creditRequest) {
			System.out.println("Credit request is in analysis state"); 
			if (creditRequest.getCreditRate() < creditRequest.getClientSalary()/3) {
			   creditRequest.setState(ACCEPTED);
			} else {
			   creditRequest.setState(REJECTED);
			}
		}
	}, ACCEPTED {
		public void doAction(CreditRequest creditRequest) {
			System.out.println("Credit request is in accepted state"); 
		}
	}, REJECTED {
		public void doAction(CreditRequest creditRequest) {
			System.out.println("Credit request is in rejected state"); 
		}
	};
	
	public abstract void doAction(CreditRequest creditRequest);

}
