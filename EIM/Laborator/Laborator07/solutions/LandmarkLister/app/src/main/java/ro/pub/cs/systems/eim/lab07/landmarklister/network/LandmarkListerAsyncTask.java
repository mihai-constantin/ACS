package ro.pub.cs.systems.eim.lab07.landmarklister.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.ResponseHandler;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import ro.pub.cs.systems.eim.lab07.landmarklister.controller.LandmarkInformationAdapter;
import ro.pub.cs.systems.eim.lab07.landmarklister.general.Constants;
import ro.pub.cs.systems.eim.lab07.landmarklister.model.LandmarkInformation;

public class LandmarkListerAsyncTask extends AsyncTask<String, Void, List<LandmarkInformation>> {

    private ListView landmarkListView;

    public LandmarkListerAsyncTask(ListView landmarkListView) {
        this.landmarkListView = landmarkListView;
    }

    @Override
    protected List<LandmarkInformation> doInBackground(String... params) {
        HttpClient httpClient = new DefaultHttpClient();
        String url = Constants.LANDMARK_LISTER_WEB_SERVICE_INTERNET_ADDRESS +
                Constants.NORTH + params[Constants.NORTH_INDEX] +
                "&" + Constants.SOUTH + params[Constants.SOUTH_INDEX] +
                "&" + Constants.EAST + params[Constants.EAST_INDEX] +
                "&" + Constants.WEST + params[Constants.WEST_INDEX] +
                "&" + Constants.CREDENTIALS;
        Log.d(Constants.TAG, url);
        HttpGet httpGet = new HttpGet(url);
        ResponseHandler<String> responseHandler = new BasicResponseHandler();
        try {
            String content = httpClient.execute(httpGet, responseHandler);
            List<LandmarkInformation> landmarkInformationList = new ArrayList<>();
            JSONObject result = new JSONObject(content);
            JSONArray jsonArray = result.getJSONArray(Constants.GEONAMES);
            for (int index = 0; index < jsonArray.length(); index++) {
                JSONObject jsonObject = jsonArray.getJSONObject(index);
                landmarkInformationList.add(new LandmarkInformation(
                        jsonObject.getDouble(Constants.LATITUDE),
                        jsonObject.getDouble(Constants.LONGITUDE),
                        jsonObject.getString(Constants.TOPONYM_NAME),
                        jsonObject.getLong(Constants.POPULATION),
                        jsonObject.getString(Constants.CODE_NAME),
                        jsonObject.getString(Constants.NAME),
                        jsonObject.getString(Constants.WIKIPEDIA_WEB_PAGE_ADDRESS),
                        jsonObject.getString(Constants.COUNTRY_CODE)
                ));
            }
            return landmarkInformationList;
        } catch (JSONException jsonException) {
            Log.e(Constants.TAG, jsonException.getMessage());
            if (Constants.DEBUG) {
                jsonException.printStackTrace();
            }
        } catch (ClientProtocolException clientProtocolException) {
            Log.e(Constants.TAG, clientProtocolException.getMessage());
            if (Constants.DEBUG) {
                clientProtocolException.printStackTrace();
            }
        } catch (IOException ioException) {
            Log.e(Constants.TAG, ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        }
        return null;
    }

    @Override
    protected void onPostExecute(List<LandmarkInformation> landmarkInformationList) {
        landmarkListView.setAdapter(new LandmarkInformationAdapter(
                landmarkListView.getContext(),
                landmarkInformationList
        ));
    }

}
