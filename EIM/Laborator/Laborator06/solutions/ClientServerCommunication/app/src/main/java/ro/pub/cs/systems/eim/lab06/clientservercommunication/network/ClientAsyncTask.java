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
            String serverAddress = params[0];
            int serverPort = Integer.parseInt(params[1]);
            socket = new Socket(serverAddress, serverPort);
            if (socket == null) {
                return null;
            }
            Log.v(Constants.TAG, "Connection opened with " + socket.getInetAddress() + ":" + socket.getLocalPort());
            BufferedReader bufferedReader = Utilities.getReader(socket);
            String currentLine;
            while ((currentLine = bufferedReader.readLine()) != null) {
                publishProgress(currentLine);
            }
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        } finally {
            try {
                if (socket != null) {
                    socket.close();
                }
                Log.v(Constants.TAG, "Connection closed");
            } catch (IOException ioException) {
                Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
                if (Constants.DEBUG) {
                    ioException.printStackTrace();
                }
            }
        }
        return null;
    }

    @Override
    protected void onPreExecute() {
        serverMessageTextView.setText("");
    }

    @Override
    protected void onProgressUpdate(String... progress) {
        serverMessageTextView.append(progress[0] + "\n");
    }

    @Override
    protected void onPostExecute(Void result) {}

}
