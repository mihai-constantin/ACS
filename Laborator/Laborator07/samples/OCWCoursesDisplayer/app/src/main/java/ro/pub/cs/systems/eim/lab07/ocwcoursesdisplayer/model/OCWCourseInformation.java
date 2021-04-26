package ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.model;

public class OCWCourseInformation {

    private String logoLocation;
    private String name;

    public OCWCourseInformation() {
        this.logoLocation = null;
        this.name = new String();
    }

    public OCWCourseInformation(String logoLocation, String name) {
        this.logoLocation = logoLocation;
        this.name = name;
    }

    public String getLogoLocation() {
        return logoLocation;
    }

    public void setLogoLocation(String logoLocation) {
        this.logoLocation = logoLocation;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
