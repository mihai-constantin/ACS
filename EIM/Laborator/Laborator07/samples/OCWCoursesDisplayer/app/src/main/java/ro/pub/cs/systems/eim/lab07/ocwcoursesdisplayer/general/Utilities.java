package ro.pub.cs.systems.eim.lab07.ocwcoursesdisplayer.general;

import android.graphics.Bitmap;
import android.graphics.Color;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import cz.msebera.android.httpclient.HttpEntity;

public class Utilities {

    public static BufferedReader getReader(HttpEntity httpEntity) throws IOException {
        return new BufferedReader(new InputStreamReader(httpEntity.getContent()));
    }

    public static Bitmap makeTransparent(Bitmap bitmap) {
        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        Bitmap bitmapCopy = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
        int[] pixels = new int[bitmapCopy.getHeight() * bitmapCopy.getWidth()];
        bitmap.getPixels(pixels,
                0,
                bitmapCopy.getWidth(),
                0,
                0,
                bitmapCopy.getWidth(),
                bitmapCopy.getHeight());
        bitmapCopy.setPixels(pixels, 0, width, 0, 0, width, height);
        for (int index = 0; index < bitmapCopy.getHeight() * bitmapCopy.getWidth(); index++) {
            if (pixels[index] == -1) {
                pixels[index] = Color.alpha(Color.TRANSPARENT);
            }
        }
        bitmapCopy.setPixels(pixels, 0, bitmapCopy.getWidth(), 0, 0, bitmapCopy.getWidth(), bitmapCopy.getHeight());
        return bitmapCopy;
    }
}
