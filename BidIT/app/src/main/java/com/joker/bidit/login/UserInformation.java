package com.joker.bidit.login;

import com.joker.bidit.dashboard.Product;

import java.util.List;

public class UserInformation {

    private static UserInformation single_instance = null;

    public String name;
    public String surname;
    public String phoneNo;
    public List<Product> products;

    public UserInformation() {
    }

    public UserInformation(String name, String surname, String phoneNo, List<Product> products) {
        this.name = name;
        this.surname = surname;
        this.phoneNo = phoneNo;
        this.products = products;
    }

    public static UserInformation getInstance() {
        return  single_instance;
    }

    public static UserInformation getInstance(String name, String surname, String phoneNo, List<Product> products)
    {
        if (single_instance == null)
            single_instance = new UserInformation(name, surname, phoneNo, products);

        return single_instance;
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

    public List<Product> getProducts() {
        return products;
    }

    public void setProducts(List<Product> products) {
        this.products = products;
    }

    public static void setSingle_instance(UserInformation single_instance) {
        UserInformation.single_instance = single_instance;
    }
}
