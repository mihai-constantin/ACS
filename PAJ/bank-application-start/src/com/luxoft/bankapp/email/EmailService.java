package com.luxoft.bankapp.email;

public class EmailService {

    private final EmailQueue emailQueue = new EmailQueue();
    private boolean isActive = true;

    public EmailService() {
        Thread emailThread = new Thread(() -> {
            while (true) {
                Email email;
                synchronized (emailQueue) {
                    try {
                        emailQueue.wait();
                    } catch (InterruptedException e) {
                        break;
                    }
                    email = emailQueue.pop();
                }
                if (email == null && !isActive) {
                    Thread.currentThread().interrupt();
                }
                if (email != null) {
                    System.out.println("=== Email === [CLIENT] " + email.getClient().getName() + " [SUBJECT] " + email.getSubject() + " [From] " + email.getFrom() + " [TO]: " + email.getTo());
                }
            }
        });
        emailThread.start();
    }

    public void sendNotificationEmail(Email email) {
        if (isActive) {
            synchronized (emailQueue) {
                this.emailQueue.add(email);
                this.emailQueue.notifyAll();
            }
        }
    }

    public void close() throws InterruptedException {
        synchronized (emailQueue) {
            this.isActive = false;
            emailQueue.notifyAll();
        }
    }
}
