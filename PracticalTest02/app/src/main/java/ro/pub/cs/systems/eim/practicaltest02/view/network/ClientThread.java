package ro.pub.cs.systems.eim.practicaltest02.view.network;

import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import ro.pub.cs.systems.eim.practicaltest02.view.general.Constants;
import ro.pub.cs.systems.eim.practicaltest02.view.general.Utilities;

public class ClientThread extends Thread {

    private String address;
    private int port;
    private String currency;
    private TextView bitValueTextView;

    private Socket socket;

    public ClientThread(String address, int port, String currency, TextView bitValueTextView) {
        this.address = address;
        this.port = port;
        this.currency = currency;
        this.bitValueTextView = bitValueTextView;
    }

    @Override
    public void run() {
        try {
            socket = new Socket(address, port);
            if (socket == null) {
                Log.e(Constants.TAG, "[CLIENT THREAD] Could not create socket!");
                return;
            }

            BufferedReader bufferedReader = Utilities.getReader(socket);
            PrintWriter printWriter = Utilities.getWriter(socket);
            if (bufferedReader == null || printWriter == null) {
                Log.e(Constants.TAG, "[CLIENT THREAD] Buffered Reader / Print Writer are null!");
                return;
            }

            // write to socket
            printWriter.println(currency);
            printWriter.flush();

            // read
            String bitInformation;
            while((bitInformation = bufferedReader.readLine()) != null) {
                final String finalizedWeatherInformation = bitInformation;
                bitValueTextView.post(new Runnable() {
                    @Override
                    public void run() {
                        bitValueTextView.setText(finalizedWeatherInformation);
                    }
                });
            }
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "[CLIENT THREAD] An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException ioException) {
                    Log.e(Constants.TAG, "[CLIENT THREAD] An exception has occurred: " + ioException.getMessage());
                    if (Constants.DEBUG) {
                        ioException.printStackTrace();
                    }
                }
            }
        }

    }
}
