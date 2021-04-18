package ro.pub.cs.systems.eim.lab06.clientservercommunication.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab06.clientservercommunication.general.Constants;

public class ClientAsyncTask extends AsyncTask<String, String, Void> {

    private TextView serverMessageTextView;

    public ClientAsyncTask(TextView serverMessageTextView) {
        this.serverMessageTextView = serverMessageTextView;
    }

    @Override
    protected Void doInBackground(String... params) {
        try {

            // TODO exercise 6b
            // - get the connection parameters (serverAddress and serverPort from parameters - on positions 0 and 1)
            // - open a socket to the server
            // - get the BufferedReader in order to read from the socket (use Utilities.getReader())
            // - while the line that has read is not null (EOF was not sent), append the content to serverMessageTextView
            // by publishing the progress - with the publishProgress(...) method - to the UI thread
            // - close the socket to the server

        } catch (Exception exception) {
            Log.e(Constants.TAG, "An exception has occurred: " + exception.getMessage());
            if (Constants.DEBUG) {
                exception.printStackTrace();
            }
        }
        return null;
    }

    @Override
    protected void onPreExecute() {
        // TODO exercise 6b
        // - reset the content of the serverMessageTextView
    }

    @Override
    protected void onProgressUpdate(String... progress) {
        // TODO exercise 6b
        // - append the content to serverMessageTextView
    }

    @Override
    protected void onPostExecute(Void result) {}

}
