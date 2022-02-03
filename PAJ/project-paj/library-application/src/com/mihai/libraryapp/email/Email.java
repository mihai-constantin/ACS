package com.mihai.libraryapp.email;

import com.mihai.libraryapp.domain.Client;

public class Email {

    private Client client;
    private String from;
    private String to;
    private String subject;
    private String body;

    public Email(Client client, String from, String to, String subject, String body) {
        this.client = client;
        this.from = from;
        this.to = to;
        this.subject = subject;
        this.body = body;
    }

    public Client getClient() {
        return client;
    }

    public void setClient(Client client) {
        this.client = client;
    }

    public String getFrom() {
        return from;
    }

    public void setFrom(String from) {
        this.from = from;
    }

    public String getTo() {
        return to;
    }

    public void setTo(String to) {
        this.to = to;
    }

    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }
}
