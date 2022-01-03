package com.luxoft.bankapp.tests;

import com.luxoft.bankapp.domain.Client;
import com.luxoft.bankapp.domain.Gender;
import org.junit.Before;
import org.junit.Test;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

import static org.junit.Assert.assertEquals;

public class Test5 {
    Set <Client> clients = new LinkedHashSet<>();

    @Before
    public void setUp() {
        clients.add(new Client("Client1", Gender.MALE, LocalDate.of(1998, 10, 5)));
        clients.add(new Client("Client2", Gender.MALE, LocalDate.of(1965, 11, 2)));
        clients.add(new Client("Client3", Gender.MALE, LocalDate.of(2000, 12, 13)));
        clients.add(new Client("Client4", Gender.MALE, LocalDate.of(1992, 1, 14)));
        clients.add(new Client("Client5", Gender.MALE, LocalDate.of(1960, 2, 2)));
        clients.add(new Client("Client6", Gender.MALE, LocalDate.of(1985, 9, 20)));
        clients.add(new Client("Client7", Gender.MALE, LocalDate.of(1990, 10, 3)));
        clients.add(new Client("Client8", Gender.MALE, LocalDate.of(1984, 11, 1)));
        clients.add(new Client("Client9", Gender.MALE, LocalDate.of(1987, 12, 7)));
        clients.add(new Client("Client10", Gender.MALE, LocalDate.of(1991, 12, 8)));
    }

    @Test
    public void testClientWithBirthdayIn30Days() {
        for (Client client : clients) {
            System.out.println(client.getName() + " " + client.getBirthday() + ": " + client.daysUntilBirthday());
        }

        Set<Client> clientsWithBirthdayInTheNext30Days = clients
                .stream()
                .filter(client -> client.daysUntilBirthday() <= 30)
                .collect(Collectors.toSet());

        System.out.println(clientsWithBirthdayInTheNext30Days);

        Set<Client> expectedClients = new HashSet<>();

        expectedClients.add(new Client("Client9", Gender.MALE, LocalDate.of(1987, 12, 7)));
        expectedClients.add(new Client("Client10", Gender.MALE, LocalDate.of(1991, 12, 8)));
        expectedClients.add(new Client("Client3", Gender.MALE, LocalDate.of(2000, 12, 13)));

        assertEquals(expectedClients, clientsWithBirthdayInTheNext30Days);
    }

    @Test
    public void clientsBirthdaysByMonth() {
        for (Client client : clients) {
            System.out.println(client.getName() + " " + client.getBirthday() + ": " + client.daysUntilBirthday());
        }

        Map<Integer, List<Client>> clientsBirthdaysByMonth = clients
                .stream()
                .collect(Collectors.groupingBy(Client::getBirthdayMonth));

        System.out.println(clientsBirthdaysByMonth);

        Map<Integer, List<Client>> expectedClients = new HashMap<>();
        expectedClients.put(1, Arrays.asList(new Client("Client4", Gender.MALE, LocalDate.of(1992, 1, 14))));
        expectedClients.put(2, Arrays.asList(new Client("Client5", Gender.MALE, LocalDate.of(1960, 2, 2))));
        expectedClients.put(9, Arrays.asList(new Client("Client6", Gender.MALE, LocalDate.of(1985, 9, 20))));
        expectedClients.put(10, Arrays.asList(new Client("Client1", Gender.MALE, LocalDate.of(1998, 10, 5)),
                new Client("Client7", Gender.MALE, LocalDate.of(1990, 10, 3))));
        expectedClients.put(11, Arrays.asList(new Client("Client2", Gender.MALE, LocalDate.of(1965, 11, 2)),
                new Client("Client8", Gender.MALE, LocalDate.of(1984, 11, 1))));
        expectedClients.put(12, Arrays.asList(new Client("Client3", Gender.MALE, LocalDate.of(2000, 12, 13)),
                new Client("Client9", Gender.MALE, LocalDate.of(1987, 12, 7)),
                new Client("Client10", Gender.MALE, LocalDate.of(1991, 12, 8))));

        assertEquals(expectedClients, clientsBirthdaysByMonth);
    }
}
