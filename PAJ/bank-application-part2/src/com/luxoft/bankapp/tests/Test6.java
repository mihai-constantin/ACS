package com.luxoft.bankapp.tests;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.domain.Gender;
import com.luxoft.bankapp.email.Email;
import com.luxoft.bankapp.email.EmailException;
import com.luxoft.bankapp.email.EmailService;

public class Test6 {

	@Test
	public void testSendMail() throws InterruptedException {
		Client client = new Client("John Smith", Gender.MALE);
		client.setCity("New York");
		client.setPhoneAreaCode("0123");
		client.setPhoneNumber("9876543");
		Client clientTo = new Client("Michael Johnson", Gender.MALE);
		clientTo.setCity("Boston");
		clientTo.setPhoneAreaCode("0121");
		clientTo.setPhoneNumber("9866543");
		Client clientCopy = new Client("Michelle Williams", Gender.FEMALE);
		clientCopy.setCity("Boston");
		clientCopy.setPhoneAreaCode("0121");
		clientCopy.setPhoneNumber("9276543");
		
		EmailService emailService = new EmailService();
		for (int i=0; i<10; i++) {
	        try {
	        	emailService.sendNotificationEmail(
				        new Email()
				                .setFrom(client)
				                .setTo(clientTo)
				                .setCopy(clientCopy)
				                .setTitle("Client Added Notification")
				                .setBody("Your e-mail has been sent!")
				);
			} catch (EmailException e) {
				e.printStackTrace();
			}
	        Thread.sleep(1000);
		}
		
        assertEquals(10, emailService.getSentEmails());

	}

}
