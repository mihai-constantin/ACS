package com.mihai.libraryapp.utils;

import com.mihai.libraryapp.domain.Client;

public interface IClientRegistrationListener {
    void onClientAdded(Client client);
}
