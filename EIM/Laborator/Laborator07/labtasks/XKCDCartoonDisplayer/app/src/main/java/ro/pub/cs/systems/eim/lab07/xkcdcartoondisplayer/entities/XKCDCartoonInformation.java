package ro.pub.cs.systems.eim.lab07.xkcdcartoondisplayer.entities;

import android.graphics.Bitmap;

public class XKCDCartoonInformation {

    private String cartoonTitle;
    private Bitmap cartoonBitmap;
    private String cartoonUrl;
    private String previousCartoonUrl, nextCartoonUrl;

    public XKCDCartoonInformation() {
        this.cartoonTitle = new String();
        this.cartoonBitmap = null;
        this.cartoonUrl = new String();
        this.previousCartoonUrl = new String();
        this.nextCartoonUrl = new String();
    }

    public XKCDCartoonInformation(String cartoonTitle,
                                  Bitmap cartoonBitmap,
                                  String cartoonUrl,
                                  String previousCartoonUrl,
                                  String nextCartoonUrl) {
        this.cartoonTitle = cartoonTitle;
        this.cartoonBitmap = cartoonBitmap;
        this.cartoonUrl = cartoonUrl;
        this.previousCartoonUrl = previousCartoonUrl;
        this.nextCartoonUrl = nextCartoonUrl;
    }

    public String getCartoonTitle() {
        return cartoonTitle;
    }

    public void setCartoonTitle(String cartoonTitle) {
        this.cartoonTitle = cartoonTitle;
    }

    public Bitmap getCartoonBitmap() {
        return cartoonBitmap;
    }

    public void setCartoonBitmap(Bitmap cartoonBitmap) {
        this.cartoonBitmap = cartoonBitmap;
    }

    public String getCartoonUrl() {
        return cartoonUrl;
    }

    public void setCartoonUrl(String cartoonUrl) {
        this.cartoonUrl = cartoonUrl;
    }

    public String getPreviousCartoonUrl() {
        return previousCartoonUrl;
    }

    public void setPreviousCartoonUrl(String previousCartoonUrl) {
        this.previousCartoonUrl = previousCartoonUrl;
    }

    public String getNextCartoonUrl() {
        return nextCartoonUrl;
    }

    public void setNextCartoonUrl(String nextCartoonUrl) {
        this.nextCartoonUrl = nextCartoonUrl;
    }

}
