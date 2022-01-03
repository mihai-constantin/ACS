package ro.pub.cs.systems.eim.lab06.pheasantgame.network;

import android.content.Context;
import android.os.Handler;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import ro.pub.cs.systems.eim.lab06.pheasantgame.general.Constants;
import ro.pub.cs.systems.eim.lab06.pheasantgame.general.Utilities;

public class ClientCommunicationThread extends Thread {

    private Socket socket = null;

    private String mostRecentWordSent = new String();
    private String mostRecentValidPrefix = new String();

    private Context context;
    private Handler handler;
    private EditText wordEditText;
    private Button sendButton;
    private TextView clientHistoryTextView;

    public ClientCommunicationThread(Socket socket, Context context, Handler handler, EditText wordEditText, Button sendButton, TextView clientHistoryTextView) {
        this.socket = socket;
        this.context = context;
        this.handler = handler;
        this.wordEditText = wordEditText;
        this.sendButton = sendButton;
        this.clientHistoryTextView = clientHistoryTextView;
        if (socket == null) {
            try {
                socket = new Socket(Constants.SERVER_HOST, Constants.SERVER_PORT);
            } catch (UnknownHostException unknownHostException) {
                Log.e(Constants.TAG, "An exception has occurred: " + unknownHostException.getMessage());
                if (Constants.DEBUG) {
                    unknownHostException.printStackTrace();
                }
            } catch (IOException ioException) {
                Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
                if (Constants.DEBUG) {
                    ioException.printStackTrace();
                }
            }
        }
        Log.d(Constants.TAG, "[CLIENT] Created communication thread with: " + socket.getInetAddress() + ":" + socket.getLocalPort());
    }

    public void run() {
        try {
            BufferedReader responseReader = Utilities.getReader(socket);
            PrintWriter requestPrintWriter = Utilities.getWriter(socket);
            final String word = wordEditText.getText().toString();
            if (word.length() > 2) {
                Log.d(Constants.TAG, "[CLIENT] Sent \"" + word + "\" on socket " + socket);
                requestPrintWriter.println(word);
                mostRecentWordSent = word;
                clientHistoryTextView.post(new Runnable() {
                    @Override
                    public void run() {
                        clientHistoryTextView.setText("Client sent word " + word + " to server\n" + clientHistoryTextView.getText().toString());
                    }
                });
            } else {
                handler.post(new Runnable() {
                    @Override
                     public void run() {
                        Toast.makeText(context, "Word must be at least 2 characters long!", Toast.LENGTH_LONG).show();
                    }
                });
            }
            final String response = responseReader.readLine();
            Log.d(Constants.TAG, "[CLIENT] Received \"" + response + "\", most recent word was \"" + mostRecentWordSent + "\" on socket " + socket);
            clientHistoryTextView.post(new Runnable() {
                @Override
                public void run() {
                    clientHistoryTextView.setText("Client received word " + response + " from server\n" + clientHistoryTextView.getText().toString());
                }
            });
            if (Constants.END_GAME.equals(response)) {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        wordEditText.setText("");
                        wordEditText.setEnabled(false);
                        sendButton.setEnabled(false);
                        clientHistoryTextView.setText("Communication ended!\n" + clientHistoryTextView.getText().toString());
                    }
                });
            } else if (mostRecentWordSent.isEmpty() || !mostRecentWordSent.equals(response)) {
                mostRecentValidPrefix = response.substring(response.length() - 2, response.length());
                wordEditText.post(new Runnable() {
                    @Override
                    public void run() {
                        wordEditText.setText(mostRecentValidPrefix);
                        wordEditText.setSelection(2);
                    }
                });
            } else {
                wordEditText.post(new Runnable() {
                    @Override
                    public void run() {
                        wordEditText.setText(mostRecentValidPrefix);
                        if ((mostRecentValidPrefix != null) && (mostRecentValidPrefix.length() == 2)) {
                            wordEditText.setSelection(2);
                        }
                    }
                });
            }
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        }
    }
}