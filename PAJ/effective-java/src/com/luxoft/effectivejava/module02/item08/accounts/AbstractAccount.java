package com.luxoft.effectivejava.module02.item08.accounts;

public abstract class AbstractAccount {
	private String id; 

	double balance;
        
    abstract void verifyAccount();

    public AbstractAccount(double balance){
        this.balance = balance;
    }
    
    public String getId() { 
    	return id; 
    } 
    
    public void setId(String id) { 
    	this.id = id; 
    }
    
    @Override
    public String toString(){
        return "Balance: " + (Math.round(balance * 100) / 100d);
    }

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		AbstractAccount other = (AbstractAccount) obj;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		return true;
	}
}