package ro.pub.cs.systems.eim.lab07.webpagekeywordsearch.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

import ro.pub.cs.systems.eim.lab07.webpagekeywordsearch.general.Constants;
import ro.pub.cs.systems.eim.lab07.webpagekeywordsearch.general.Utilities;

public class WebPageKeywordSearchAsyncTask extends AsyncTask<String, Void, String> {

    private TextView resultsTextView;

    public WebPageKeywordSearchAsyncTask(TextView resultsTextView) {
        this.resultsTextView = resultsTextView;
    }

    @Override
    protected String doInBackground(String... params) {
        HttpURLConnection httpURLConnection = null;
        StringBuilder result = new StringBuilder();
        String error = null;
        try {
            String webPageAddress = params[0];
            String keyword = params[1];
            if (webPageAddress == null || webPageAddress.isEmpty()) {
                error = "Web Page address cannot be empty";
            }
            if (keyword == null || keyword.isEmpty()) {
                error = "Keyword cannot be empty";
            }
            if (error != null) {
                return error;
            }
            URL url = new URL(webPageAddress);
            result.append("Protocol: " + url.getProtocol() + "\n");
            result.append("Host: " + url.getHost() + "\n");
            result.append("Port: " + url.getPort() + "\n");
            result.append("File: " + url.getFile() + "\n");
            result.append("Reference: " + url.getRef() + "\n");
            result.append("==========\n");
            URLConnection urlConnection = url.openConnection();
            if (urlConnection instanceof HttpURLConnection) {
                httpURLConnection = (HttpURLConnection)urlConnection;
                BufferedReader bufferedReader = Utilities.getReader(httpURLConnection);
                int currentLineNumber = 0, numberOfOccurrences = 0;
                String currentLineContent;
                while ((currentLineContent = bufferedReader.readLine()) != null) {
                    currentLineNumber++;
                    if (currentLineContent.contains(keyword)) {
                        result.append("line: " + currentLineNumber + " / " + currentLineContent + "\n");
                        numberOfOccurrences++;
                    }
                }
                result.append("Number of occurrences: " + numberOfOccurrences + "\n");
                return result.toString();
            }
        } catch (MalformedURLException malformedURLException) {
            Log.e(Constants.TAG, malformedURLException.getMessage());
            if (Constants.DEBUG) {
                malformedURLException.printStackTrace();
            }
        } catch (IOException ioException) {
            Log.e(Constants.TAG, ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        } catch (Exception exception) {
            Log.e(Constants.TAG, exception.getMessage());
            if (Constants.DEBUG) {
                exception.printStackTrace();
            }
        } finally {
            if (httpURLConnection != null) {
                httpURLConnection.disconnect();
            }
        }
        return null;
    }

    @Override
    protected void onPostExecute(String result) {
        resultsTextView.setText(result);
    }
}
