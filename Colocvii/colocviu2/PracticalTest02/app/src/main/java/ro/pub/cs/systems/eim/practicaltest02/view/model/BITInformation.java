package ro.pub.cs.systems.eim.practicaltest02.view.model;

public class BITInformation {

    private String EUR;
    private String USD;

    public BITInformation() {
        this.EUR = null;
        this.USD = null;
    }

    public BITInformation(String EUR, String USD) {
        this.EUR = EUR;
        this.USD = USD;
    }

    public String getEUR() {
        return EUR;
    }

    public void setEUR(String EUR) {
        this.EUR = EUR;
    }

    public String getUSD() {
        return USD;
    }

    public void setUSD(String USD) {
        this.USD = USD;
    }

    @Override
    public String toString() {
        return "BITInformation{" +
                "EUR='" + EUR + '\'' +
                ", USD='" + USD + '\'' +
                '}';
    }
}
