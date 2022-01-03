package ro.pub.cs.systems.eim.lab06.clientservercommunication.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;

import ro.pub.cs.systems.eim.lab06.clientservercommunication.general.Constants;
import ro.pub.cs.systems.eim.lab06.clientservercommunication.general.Utilities;

public class ClientAsyncTask extends AsyncTask<String, String, Void> {

    private TextView serverMessageTextView;

    public ClientAsyncTask(TextView serverMessageTextView) {
        this.serverMessageTextView = serverMessageTextView;
    }

    @Override
    protected Void doInBackground(String... params) {
        Socket socket = null;
        try {
            // exercise 6b
            // - get the connection parameters (serverAddress and serverPort from parameters - on positions 0 and 1)
            String serverAddress = params[0];
            Integer serverPort = Integer.valueOf(params[1]);

            // - open a socket to the server
            socket = new Socket(serverAddress, serverPort);
            Log.v(Constants.TAG, "Connected to: " + socket.getInetAddress() + ":" + socket.getLocalPort());

            // - get the BufferedReader in order to read from the socket (use Utilities.getReader())
            BufferedReader bufferedReader = Utilities.getReader(socket);

            // - while the line that has read is not null (EOF was not sent), append the content to serverMessageTextView
            // by publishing the progress - with the publishProgress(...) method - to the UI thread
            String line = bufferedReader.readLine();
            while(line != null) {
                publishProgress(line);
                line = bufferedReader.readLine();
            }
        } catch (Exception exception) {
            Log.e(Constants.TAG, "An exception has occurred: " + exception.getMessage());
            if (Constants.DEBUG) {
                exception.printStackTrace();
            }
        } finally {
            // - close the socket to the server
            try {
                if (socket != null) {
                    socket.close();
                }
            } catch (IOException ioException) {
                Log.d(Constants.TAG, ioException.getMessage());
                if (Constants.DEBUG) {
                    ioException.printStackTrace();
                }
            }
        }
        return null;
    }

    @Override
    protected void onPreExecute() {
        // exercise 6b
        // - reset the content of the serverMessageTextView
        serverMessageTextView.setText("");
    }

    @Override
    protected void onProgressUpdate(String... progress) {
        // TODO exercise 6b
        // - append the content to serverMessageTextView
        serverMessageTextView.append(progress[0] + "\n");
    }

    @Override
    protected void onPostExecute(Void result) {}

}
