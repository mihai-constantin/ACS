package ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.model;

import android.graphics.Bitmap;

public class OCWCourseContent {

    private Bitmap logo;
    private String name;

    public OCWCourseContent() {
        this.logo = null;
        this.name = new String();
    }

    public OCWCourseContent(Bitmap logo, String name) {
        this.logo = logo;
        this.name = name;
    }

    public Bitmap getLogo() {
        return logo;
    }

    public void setLogo(Bitmap logo) {
        this.logo = logo;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
