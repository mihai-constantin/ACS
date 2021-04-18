package ro.pub.cs.systems.eim.lab06.daytimeprotocol.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import ro.pub.cs.systems.eim.lab06.daytimeprotocol.general.Constants;
import ro.pub.cs.systems.eim.lab06.daytimeprotocol.general.Utilities;

public class NISTCommunicationAsyncTask extends AsyncTask<Void, Void, String> {

    private TextView dayTimeProtocolTextView;

    public NISTCommunicationAsyncTask(TextView dayTimeProtocolTextView) {
        this.dayTimeProtocolTextView = dayTimeProtocolTextView;
    }

    @Override
    protected String doInBackground(Void... params) {
        String dayTimeProtocol = null;
        Socket socket = null;
        try {
            socket = new Socket(Constants.NIST_SERVER_HOST, Constants.NIST_SERVER_PORT);
            BufferedReader bufferedReader = Utilities.getReader(socket);
            bufferedReader.readLine();
            dayTimeProtocol = bufferedReader.readLine();
            Log.d(Constants.TAG, "The server returned: " + dayTimeProtocol);
            socket.close();
        } catch (UnknownHostException unknownHostException) {
            Log.d(Constants.TAG, unknownHostException.getMessage());
            if (Constants.DEBUG) {
                unknownHostException.printStackTrace();
            }
        } catch (IOException ioException) {
            Log.d(Constants.TAG, ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        } finally {
            try {
                socket.close();
            } catch (IOException ioException) {
                Log.d(Constants.TAG, ioException.getMessage());
                if (Constants.DEBUG) {
                    ioException.printStackTrace();
                }
            }
        }
        return dayTimeProtocol;
    }

    @Override
    protected void onPostExecute(String result) {
        dayTimeProtocolTextView.setText(result);
    }

}
