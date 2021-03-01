/*
 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
 */

/**
 * Class for a message exchanged between space explorers and headquarters.
 */
public class Message {
	private int parentSolarSystem;
	private int currentSolarSystem;
	private String data;

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Creates a {@code Message} object to be sent from a space explorer to an HQ.
	 * 
	 * @param parentSolarSystem
	 *            the previous solar system
	 * @param currentSolarSystem
	 *            the current solar system
	 * @param data
	 *            the data contained in the message (i.e., decoded frequency)
	 */
	public Message(int parentSolarSystem, int currentSolarSystem, String data) {
		this.parentSolarSystem = parentSolarSystem;
		this.currentSolarSystem = currentSolarSystem;
		this.data = data;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Creates a {@code Message} object to be sent from an HQ to a space explorer.
	 * 
	 * @param currentSolarSystem
	 *            the current solar system
	 * @param data
	 *            data contained in the message (i.e., undecoded frequency)
	 */
	public Message(int currentSolarSystem, String data) {
		this.currentSolarSystem = currentSolarSystem;
		this.data = data;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Gets the parent solar system from the message.
	 * 
	 * @return the parent solar system ID
	 */
	public int getParentSolarSystem() {
		return parentSolarSystem;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Sets the parent solar system in the message.
	 * 
	 * @param parentSolarSystem
	 *            the parent solar system ID to be set
	 */
	public void setParentSolarSystem(int parentSolarSystem) {
		this.parentSolarSystem = parentSolarSystem;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Gets the current solar system from the message.
	 * 
	 * @return the current solar system ID
	 */
	public int getCurrentSolarSystem() {
		return currentSolarSystem;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Sets the current solar system in the message.
	 * 
	 * @param currentSolarSystem
	 *            the current solar system ID to be set
	 */
	public void setCurrentSolarSystem(int currentSolarSystem) {
		this.currentSolarSystem = currentSolarSystem;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Gets the data in the message.
	 * 
	 * @return the data in the message
	 */
	public String getData() {
		return data;
	}

	/*
	 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
	 */

	/**
	 * Sets the data in the message.
	 * 
	 * @param data
	 *            the data to be set in the message
	 */
	public void setData(String data) {
		this.data = data;
	}
}

/*
 * DO NOT MODIFY THIS FILE! IT WILL BE AUTOMATICALLY OVERWRITTEN BY THE CHECKER!
 */
