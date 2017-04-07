package ro.pub.cs.systems.eim.lab06.clientservercommunication.network;

import android.util.Log;
import android.widget.EditText;

import java.io.IOException;
import java.net.Socket;

import ro.pub.cs.systems.eim.lab06.clientservercommunication.general.Constants;

public class CommunicationThread extends Thread {

    private Socket socket;
    private EditText serverTextEditText;

    public CommunicationThread(Socket socket, EditText serverTextEditText) {
        this.socket = socket;
        this.serverTextEditText = serverTextEditText;
    }

    @Override
    public void run() {
        try {
            Log.v(Constants.TAG, "Connection opened with " + socket.getInetAddress() + ":" + socket.getLocalPort());

            // TODO exercise 6a
            // - get the PrintWriter object in order to write on the socket (use Utilities.getWriter())
            // - print a line containing the text in the serverTextEditText edit text

            socket.close();
            Log.v(Constants.TAG, "Connection closed");
        } catch (Exception exception) {
            Log.e(Constants.TAG, "An exception has occurred: " + exception.getMessage());
            if (Constants.DEBUG) {
                exception.printStackTrace();
            }
        }
    }

}
