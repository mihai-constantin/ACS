package com.mihai.libraryapp.email;

import java.util.ArrayList;
import java.util.List;

public class EmailQueue {

    private final List<Email> emailQueue = new ArrayList<>();

    public void add(Email email) {
        emailQueue.add(email);
    }

    public Email pop() {
        if (emailQueue.size() == 0) {
            return null;
        }
        return emailQueue.remove(0);
    }
}
