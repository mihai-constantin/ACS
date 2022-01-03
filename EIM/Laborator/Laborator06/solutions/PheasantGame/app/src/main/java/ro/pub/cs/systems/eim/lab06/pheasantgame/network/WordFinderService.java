package ro.pub.cs.systems.eim.lab06.pheasantgame.network;

import android.os.AsyncTask;
import android.util.Log;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;

import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.ResponseHandler;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import ro.pub.cs.systems.eim.lab06.pheasantgame.general.Constants;

public class WordFinderService extends AsyncTask<String, Object, List<String>> {
    @Override
    protected List<String> doInBackground(String... params) {
        HttpClient httpClient = new DefaultHttpClient();
        HttpGet httpGet = new HttpGet(Constants.WORD_FINDER_SERVICE_INTERNET_ADDRESS + params[0] + ".html");
        ResponseHandler<String> responseHandler = new BasicResponseHandler();
        String content = null;
        try {
            content = httpClient.execute(httpGet, responseHandler);
        } catch (ClientProtocolException clientProtocolException) {
            Log.d(Constants.TAG, "An exception has occurred: " + clientProtocolException.getMessage());
            if (Constants.DEBUG) {
                clientProtocolException.printStackTrace();
            }
        } catch (IOException ioException) {
            Log.d(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        }
        Document htmlPage = Jsoup.parse(content);
        List<String> wordList = new LinkedList<>();
        for (Element element: htmlPage.getElementsByClass(Constants.WORD_TAG)) {
            wordList.add(element.html());
        }
        Log.d(Constants.TAG, wordList.toString());
        return wordList;
    }
}
