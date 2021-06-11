package ro.pub.cs.systems.eim.practicaltest02.model;

public class EarthquakeInformation {

    private String id;
    private String magnitude;
    private String lng;
    private String src;
    private String datetime;
    private String depth;
    private String lat;

    public EarthquakeInformation() {
        this.id = null;
        this.magnitude = null;
        this.lng = null;
        this.src = null;
        this.datetime = null;
        this.depth = null;
        this.lat = null;
    }

    public EarthquakeInformation(String id, String magnitude, String lng, String src, String datetime, String depth, String lat) {
        this.id = id;
        this.magnitude = magnitude;
        this.lng = lng;
        this.src = src;
        this.datetime = datetime;
        this.depth = depth;
        this.lat = lat;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getMagnitude() {
        return magnitude;
    }

    public void setMagnitude(String magnitude) {
        this.magnitude = magnitude;
    }

    public String getLng() {
        return lng;
    }

    public void setLng(String lng) {
        this.lng = lng;
    }

    public String getSrc() {
        return src;
    }

    public void setSrc(String src) {
        this.src = src;
    }

    public String getDatetime() {
        return datetime;
    }

    public void setDatetime(String datetime) {
        this.datetime = datetime;
    }

    public String getDepth() {
        return depth;
    }

    public void setDepth(String depth) {
        this.depth = depth;
    }

    public String getLat() {
        return lat;
    }

    public void setLat(String lat) {
        this.lat = lat;
    }

    @Override
    public String toString() {
        return "EarthquakeInformation{" +
                "id='" + id + '\'' +
                ", magnitude='" + magnitude + '\'' +
                ", lng='" + lng + '\'' +
                ", src='" + src + '\'' +
                ", datetime='" + datetime + '\'' +
                ", depth='" + depth + '\'' +
                ", lat='" + lat + '\'' +
                '}';
    }
}
