package ro.pub.systems.eim.lab02.activitylifecyclemonitor.general;

import android.content.Context;
import android.util.Log;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserException;
import org.xmlpull.v1.XmlPullParserFactory;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import ro.pub.systems.eim.lab02.activitylifecyclemonitor.entities.Credential;

public class Utilities {

    public static boolean allowAccess(Context context, String username, String password) {
        try {
            Log.i(Constants.TAG, "username: " + username + " password: " + password);
            XmlPullParserFactory xmlPullParserFactory = XmlPullParserFactory.newInstance();
            XmlPullParser xmlPullParser = xmlPullParserFactory.newPullParser();
            InputStream inputStream = context.getAssets().open(Constants.CREDENTIAL_FILE);
            xmlPullParser.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES, false);
            xmlPullParser.setInput(inputStream, null);
            List<Credential> credentials = parseXml(xmlPullParser);
            for (Credential credential: credentials) {
                Log.i(Constants.TAG, "credential.getUsername(): " + credential.getUsername() + " credential.getPassword(): " + credential.getPassword());
                if (credential.getUsername().equals(username) && credential.getPassword().equals(password)) {
                    return true;
                }
            }
        } catch (XmlPullParserException xmlPullParserException) {
            xmlPullParserException.printStackTrace();
            if (Constants.DEBUG) {
                Log.e(Constants.TAG, "An exception has occurred: " + xmlPullParserException.getMessage());
            }
        } catch (IOException ioException) {
            ioException.printStackTrace();
            if (Constants.DEBUG) {
                Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            }
        }
        return false;
    }

    public static List<Credential> parseXml(XmlPullParser xmlPullParser) throws  XmlPullParserException, IOException {
        List<Credential> credentialsList = null;
        int eventType = xmlPullParser.getEventType();
        Credential currentCredential = null;
        while (eventType != XmlPullParser.END_DOCUMENT) {
            String tag = null;
            switch (eventType) {
                case XmlPullParser.START_DOCUMENT:
                    credentialsList = new ArrayList<>();
                    break;
                case XmlPullParser.START_TAG:
                    tag = xmlPullParser.getName();
                    if (Constants.CREDENTIAL_TAG.equalsIgnoreCase(tag)) {
                        currentCredential = new Credential();
                    } else if (currentCredential != null) {
                        if (Constants.USERNAME_TAG.equalsIgnoreCase(tag)) {
                            currentCredential.setUsername(xmlPullParser.nextText());
                        } else if (Constants.PASSWORD_TAG.equalsIgnoreCase(tag)) {
                            currentCredential.setPassword(xmlPullParser.nextText());
                        }
                    }
                    break;
                case XmlPullParser.END_TAG:
                    tag = xmlPullParser.getName();
                    if (Constants.CREDENTIAL_TAG.equalsIgnoreCase(tag) && currentCredential != null) {
                        credentialsList.add(currentCredential);
                    }
                    break;
                case XmlPullParser.END_DOCUMENT:
                    return credentialsList;
            }
            eventType = xmlPullParser.next();
        }
        return credentialsList;
    }

}
