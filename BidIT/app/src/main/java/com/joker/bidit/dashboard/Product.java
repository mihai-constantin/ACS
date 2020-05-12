package com.joker.bidit.dashboard;

public class Product {

    private String mColor;
    private Double mWeight;
    private String mName;
    private double mPrice;
    private String mPicture;

    public Product() {

    }

    public Product(String mColor, Double mWeight, String mName, double mPrice, String mPicture) {
        this.mColor = mColor;
        this.mWeight = mWeight;
        this.mName = mName;
        this.mPrice = mPrice;
        this.mPicture = mPicture;
    }

    public String getName() {
        return mName;
    }

    public void setName(String mName) {
        this.mName = mName;
    }

    public Double getPrice() {
        return mPrice;
    }

    public void setPrice(Double mPrice) {
        this.mPrice = mPrice;
    }

    public Double getWeight() {
        return mWeight;
    }

    public void setWeight(Double mWeight) {
        this.mWeight = mWeight;
    }

    public String getColor() {
        return mColor;
    }

    public void setColour(String mColour) {
        this.mColor = mColour;
    }

    public String getPicture() {
        return mPicture;
    }

    public void setPicture(String mPicture) {
        this.mPicture = mPicture;
    }


}
