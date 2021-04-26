package ro.pub.cs.systems.eim.lab07.googlesearcher.general;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import cz.msebera.android.httpclient.HttpEntity;

public class Utilities {

    public static BufferedReader getReader(HttpEntity httpEntity) throws IOException {
        return new BufferedReader(new InputStreamReader(httpEntity.getContent()));
    }

}
