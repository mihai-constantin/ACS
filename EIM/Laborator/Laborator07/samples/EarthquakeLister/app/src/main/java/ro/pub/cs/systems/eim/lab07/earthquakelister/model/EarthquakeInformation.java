package ro.pub.cs.systems.eim.lab07.earthquakelister.model;

public class EarthquakeInformation {

    private double latitude, longitude;
    private double magnitude;
    private double depth;
    private String source;
    private String dateAndTime;

    public EarthquakeInformation() {
        this.latitude = 0.0d;
        this.longitude = 0.0d;
        this.magnitude = 0.0d;
        this.depth = 0.0d;
        this.source = new String();
        this.dateAndTime = new String();
    }

    public EarthquakeInformation(double latitude, double longitude, double magnitude, double depth, String source, String dateAndTime) {
        this.latitude = latitude;
        this.longitude = longitude;
        this.magnitude = magnitude;
        this.depth = depth;
        this.source = source;
        this.dateAndTime = dateAndTime;
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

    public double getMagnitude() {
        return magnitude;
    }

    public void setMagnitude(double magnitude) {
        this.magnitude = magnitude;
    }

    public double getDepth() {
        return depth;
    }

    public void setDepth(double depth) {
        this.depth = depth;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getDateAndTime() {
        return dateAndTime;
    }

    public void setDateAndTime(String dateAndTime) {
        this.dateAndTime = dateAndTime;
    }
}
