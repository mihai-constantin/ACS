package com.joker.bidit.login;

public class UserInformation {

    public String name;
    public String surname;
    public String phoneNo;

    public UserInformation() {
    }

    public UserInformation (String name, String surname, String phoneNo) {
        this.name = name;
        this.surname = surname;
        this.phoneNo = phoneNo;
    }

    public String getUserName() {
        return name;
    }

    public String getUserSurname() {
        return surname;
    }

    public String getUserPhoneNo() {
        return phoneNo;
    }
}
