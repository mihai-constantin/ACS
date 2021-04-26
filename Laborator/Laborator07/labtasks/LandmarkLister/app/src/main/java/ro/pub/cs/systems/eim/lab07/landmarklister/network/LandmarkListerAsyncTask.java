package ro.pub.cs.systems.eim.lab07.landmarklister.network;

import android.os.AsyncTask;
import android.widget.ListView;

import java.util.List;

import ro.pub.cs.systems.eim.lab07.landmarklister.model.LandmarkInformation;

public class LandmarkListerAsyncTask extends AsyncTask<String, Void, List<LandmarkInformation>> {

    private ListView landmarkListView;

    public LandmarkListerAsyncTask(ListView landmarkListView) {
        this.landmarkListView = landmarkListView;
    }

    @Override
    protected List<LandmarkInformation> doInBackground(String... params) {

        // TODO exercise 7
        // - create an instance of a HttpClient object
        // - create the URL to the web service, appending the bounding box coordinates and the username to the base Internet address
        // - create an instance of a HttGet object
        // - create an instance of a ReponseHandler object
        // - execute the request, thus obtaining the response
        // - get the JSON object representing the response
        // - get the JSON array (the value corresponding to the "geonames" attribute)
        // - iterate over the results list and create a LandmarkInformation for each element

        return null;
    }

    @Override
    protected void onPostExecute(List<LandmarkInformation> landmarkInformationList) {

        // TODO exercise 7
        // create a LandmarkInformationAdapter with the array and attach it to the landmarksListView

    }

}
