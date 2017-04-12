package ro.pub.cs.systems.eim.lab06.multiplethreadedserver.network;

import android.util.Log;
import android.widget.EditText;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import ro.pub.cs.systems.eim.lab06.multiplethreadedserver.general.Constants;
import ro.pub.cs.systems.eim.lab06.multiplethreadedserver.general.Utilities;

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
            try {
                Thread.sleep(3000);
            } catch (InterruptedException interruptedException) {
                Log.e(Constants.TAG, "An exception has occurred: " + interruptedException.getMessage());
                if (Constants.DEBUG) {
                    interruptedException.printStackTrace();
                }
            }
            PrintWriter printWriter = Utilities.getWriter(socket);
            printWriter.println(serverTextEditText.getText().toString());
            socket.close();
            Log.v(Constants.TAG, "Connection closed");
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        }
    }

}
