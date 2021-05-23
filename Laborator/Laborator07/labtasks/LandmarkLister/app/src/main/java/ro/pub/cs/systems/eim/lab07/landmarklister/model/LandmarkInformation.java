package ro.pub.cs.systems.eim.lab07.landmarklister.model;

public class LandmarkInformation {

    private double latitude, longitude;
    private String toponymName;
    private long population;
    private String codeName;
    private String name;
    private String wikipediaWebPageAddressName;
    private String countryCode;

    public LandmarkInformation() {
        this.latitude = 0.0d;
        this.longitude = 0.0d;
        this.toponymName = new String();
        this.population = 0;
        this.codeName = new String();
        this.name = new String();
        this.wikipediaWebPageAddressName = new String();
        this.countryCode = new String();
    }

    public LandmarkInformation(double latitude, double longitude, String toponymName, long population, String codeName, String name, String wikipediaWebPageAddressName, String countryCode) {
        this.latitude = latitude;
        this.longitude = longitude;
        this.toponymName = toponymName;
        this.population = population;
        this.codeName = codeName;
        this.name = name;
        this.wikipediaWebPageAddressName = wikipediaWebPageAddressName;
        this.countryCode = countryCode;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public String getToponymName() {
        return toponymName;
    }

    public void setToponymName(String toponymName) {
        this.toponymName = toponymName;
    }

    public long getPopulation() {
        return population;
    }

    public void setPopulation(long population) {
        this.population = population;
    }

    public String getCodeName() {
        return codeName;
    }

    public void setCodeName(String codeName) {
        this.codeName = codeName;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getWikipediaWebPageAddressName() {
        return wikipediaWebPageAddressName;
    }

    public void setWikipediaWebPageAddressName(String wikipediaWebPageAddressName) {
        this.wikipediaWebPageAddressName = wikipediaWebPageAddressName;
    }

    public String getCountryCode() {
        return countryCode;
    }

    public void setCountryCode(String countryCode) {
        this.countryCode = countryCode;
    }
}
