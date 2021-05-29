package ro.pub.cs.systems.eim.practicaltest02.network;

import android.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.HashMap;

import cz.msebera.android.httpclient.HttpEntity;
import cz.msebera.android.httpclient.HttpResponse;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import cz.msebera.android.httpclient.util.EntityUtils;
import ro.pub.cs.systems.eim.practicaltest02.general.Constants;
import ro.pub.cs.systems.eim.practicaltest02.general.Utilities;
import ro.pub.cs.systems.eim.practicaltest02.model.EarthquakeInformation;

public class CommunicationThread extends Thread {

    private ServerThread serverThread;
    private Socket socket;

    public CommunicationThread(ServerThread serverThread, Socket socket) {
        this.serverThread = serverThread;
        this.socket = socket;
    }

    @Override
    public void run() {
        if (socket == null) {
            Log.e(Constants.TAG, "[COMMUNICATION THREAD] Socket is null!");
            return;
        }
        try {
            BufferedReader bufferedReader = Utilities.getReader(socket);
            PrintWriter printWriter = Utilities.getWriter(socket);
            if (bufferedReader == null || printWriter == null) {
                Log.e(Constants.TAG, "[COMMUNICATION THREAD] BufferedReader/PrintWriter are null!");
                return;
            }

            Log.i(Constants.TAG, "[COMMUNICATION THREAD] Waiting for parameters from client (city / information type)!");
            // read from client
            String north = bufferedReader.readLine();
            String south = bufferedReader.readLine();
            String west = bufferedReader.readLine();
            String east = bufferedReader.readLine();
            String informationType = bufferedReader.readLine();
            if (north == null || north.isEmpty()
                    || south == null || south.isEmpty()
                    || west == null || west.isEmpty()
                    || east == null || east.isEmpty()
                    || informationType == null || informationType.isEmpty()) {
                Log.e(Constants.TAG, "[COMMUNICATION THREAD] Error receiving parameters from client!");
                return;
            }

            String city = north + south + west + east;
            HashMap<String, EarthquakeInformation> data = serverThread.getData();
            EarthquakeInformation earthquakeInformation = null;
            if (data.containsKey(city)) {
                Log.i(Constants.TAG, "[COMMUNICATION THREAD] Getting the information from the cache...");
                earthquakeInformation = data.get(city);
            } else {
                Log.i(Constants.TAG, "[COMMUNICATION THREAD] Getting the information from the webservice...");
                HttpClient httpClient = new DefaultHttpClient();
                String pageSourceCode = "";

                HttpGet httpGet = new HttpGet(Constants.WEB_SERVICE_ADDRESS + "?north=" + north + "&south=" + south + "&east=" + east + "&west=" + west + "&username=" + Constants.WEB_SERVICE_API_KEY);
                HttpResponse httpGetResponse = httpClient.execute(httpGet);
                HttpEntity httpGetEntity = httpGetResponse.getEntity();
                if (httpGetEntity != null) {
                    pageSourceCode = EntityUtils.toString(httpGetEntity);
                }

                if (pageSourceCode == null) {
                    Log.e(Constants.TAG, "[COMMUNICATION THREAD] Error getting the information from the webservice!");
                    return;
                }
                Log.i(Constants.TAG, pageSourceCode);

                // process pageSourceCode
                JSONObject content = new JSONObject(pageSourceCode);
                JSONArray earthquakeArray = content.getJSONArray(Constants.EARTHQUAKE);
                JSONObject earthquake = earthquakeArray.getJSONObject(0);

                earthquakeInformation = new EarthquakeInformation(
                        earthquake.getString(Constants.ID),
                        earthquake.getString(Constants.MAGNITUDE),
                        earthquake.getString(Constants.LNG),
                        earthquake.getString(Constants.SRC),
                        earthquake.getString(Constants.DATETIME),
                        earthquake.getString(Constants.DEPTH),
                        earthquake.getString(Constants.LAT));

                serverThread.setData(city, earthquakeInformation);
            }

            if (earthquakeInformation == null) {
                Log.e(Constants.TAG, "[COMMUNICATION THREAD] Weather Forecast Information is null!");
                return;
            }

            String result = null;
            switch (informationType) {
                case Constants.ALL:
                    result = earthquakeInformation.toString();
                    break;
                case Constants.ID:
                    result = earthquakeInformation.getId();
                    break;
                case Constants.MAGNITUDE:
                    result = earthquakeInformation.getMagnitude();
                    break;
                case Constants.LNG:
                    result = earthquakeInformation.getLng();
                    break;
                case Constants.SRC:
                    result = earthquakeInformation.getSrc();
                    break;
                case Constants.DATETIME:
                    result = earthquakeInformation.getDatetime();
                    break;
                case Constants.DEPTH:
                    result = earthquakeInformation.getDepth();
                    break;
                case Constants.LAT:
                    result = earthquakeInformation.getLat();
                    break;
                default:
                    result = "[COMMUNICATION THREAD] Wrong information type!";
            }
            // write to socket
            printWriter.println(result);
            printWriter.flush();
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "[COMMUNICATION THREAD] An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        } catch (JSONException jsonException) {
            Log.e(Constants.TAG, "[COMMUNICATION THREAD] An exception has occurred: " + jsonException.getMessage());
            if (Constants.DEBUG) {
                jsonException.printStackTrace();
            }
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException ioException) {
                    Log.e(Constants.TAG, "[COMMUNICATION THREAD] An exception has occurred: " + ioException.getMessage());
                    if (Constants.DEBUG) {
                        ioException.printStackTrace();
                    }
                }
            }
        }
    }
}
