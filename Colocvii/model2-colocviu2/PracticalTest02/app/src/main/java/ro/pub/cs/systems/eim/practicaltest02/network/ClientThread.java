package ro.pub.cs.systems.eim.practicaltest02.network;

import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import ro.pub.cs.systems.eim.practicaltest02.general.Constants;
import ro.pub.cs.systems.eim.practicaltest02.general.Utilities;

public class ClientThread extends Thread {

    private String address;
    private int port;
    private String north;
    private String south;
    private String west;
    private String east;
    private String informationType;
    private TextView weatherForecastTextView;

    private Socket socket;

    public ClientThread(String address, int port, String north, String south, String west, String east, String informationType, TextView weatherForecastTextView) {
        this.address = address;
        this.port = port;
        this.north = north;
        this.south = south;
        this.west = west;
        this.east = east;
        this.informationType = informationType;
        this.weatherForecastTextView = weatherForecastTextView;
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
            printWriter.println(north);
            printWriter.flush();
            printWriter.println(south);
            printWriter.flush();
            printWriter.println(west);
            printWriter.flush();
            printWriter.println(east);
            printWriter.flush();
            printWriter.println(informationType);
            printWriter.flush();

            // read
            String earthquakeInformation;
            while((earthquakeInformation = bufferedReader.readLine()) != null) {
                final String finalizedWeatherInformation = earthquakeInformation;
                weatherForecastTextView.post(new Runnable() {
                    @Override
                    public void run() {
                        weatherForecastTextView.setText(finalizedWeatherInformation);
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
