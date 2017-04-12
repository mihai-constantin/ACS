package ro.pub.cs.systems.eim.lab06.pheasantgame.network;

import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.List;
import java.util.Random;

import ro.pub.cs.systems.eim.lab06.pheasantgame.general.Constants;
import ro.pub.cs.systems.eim.lab06.pheasantgame.general.Utilities;

public class ServerCommunicationThread extends Thread {

    private Socket socket;
    private TextView serverHistoryTextView;

    private Random random = new Random();

    private String expectedWordPrefix = new String();

    public ServerCommunicationThread(Socket socket, TextView serverHistoryTextView) {
        if (socket != null) {
            this.socket = socket;
            Log.d(Constants.TAG, "[SERVER] Created communication thread with: " + socket.getInetAddress() + ":" + socket.getLocalPort());
        }
        this.serverHistoryTextView = serverHistoryTextView;
    }

    public void run() {
        try {
            if (socket == null) {
                return;
            }
            boolean isRunning = true;
            BufferedReader requestReader = Utilities.getReader(socket);
            PrintWriter responsePrintWriter = Utilities.getWriter(socket);

            while (isRunning) {
                Log.d(Constants.TAG, "[SERVER] Waiting to receive data with prefix \"" + expectedWordPrefix + "\" on socket " + socket);
                String request = requestReader.readLine();
                final String finalizedRequest1 = request;
                serverHistoryTextView.post(new Runnable() {
                    @Override
                    public void run() {
                        serverHistoryTextView.setText("Server received word " + finalizedRequest1 + " from client\n" + serverHistoryTextView.getText().toString());
                    }
                });
                Log.d(Constants.TAG, "[SERVER] Received " + request + " on socket " + socket);

                if (Constants.END_GAME.equals(request)) {
                    Log.d(Constants.TAG, "[SERVER] Sent \"" + Constants.END_GAME + "\" on socket " + socket);
                    responsePrintWriter.println(Constants.END_GAME);
                    serverHistoryTextView.post(new Runnable() {
                        @Override
                        public void run() {
                            serverHistoryTextView.setText("Communication ended!\n" + serverHistoryTextView.getText().toString());
                        }
                    });
                    isRunning = false;
                } else {
                    if ((Utilities.wordValidation(request)) && (request.length() > 2) && (expectedWordPrefix.isEmpty() || request.startsWith(expectedWordPrefix))) {
                        String wordPrefix = request.substring(request.length()-2, request.length());
                        List<String> wordList = Utilities.getWordListStartingWith(wordPrefix);

                        if (wordList.isEmpty()) {
                            Log.d(Constants.TAG, "[SERVER] Sent \"" + Constants.END_GAME + "\" on socket " + socket);
                            responsePrintWriter.println(Constants.END_GAME);
                            serverHistoryTextView.post(new Runnable() {
                                @Override
                                public void run() {
                                    serverHistoryTextView.setText("Server sent word \"" + Constants.END_GAME + "\" to client because it was locked out\n" + serverHistoryTextView.getText().toString());
                                }
                            });
                            isRunning = false;
                        } else {
                            int wordIndex = random.nextInt(wordList.size());
                            final String word = wordList.get(wordIndex);
                            expectedWordPrefix = word.substring(word.length()-2, word.length());
                            Log.d(Constants.TAG, "[SERVER] Sent \"" + word + "\" on socket " + socket);
                            responsePrintWriter.println(wordList.get(wordIndex));
                            serverHistoryTextView.post(new Runnable() {
                                @Override
                                public void run() {
                                    serverHistoryTextView.setText("Server sent word " + word + " to client\n" + serverHistoryTextView.getText().toString());
                                }
                            });
                        }
                    } else {
                        Log.d(Constants.TAG, "[SERVER] Sent \"" + request + "\" on socket " + socket);
                        responsePrintWriter.println(request);
                        final String finalizedRequest2 = request;
                        serverHistoryTextView.post(new Runnable() {
                            @Override
                            public void run() {
                                serverHistoryTextView.setText("Server sent back the word " + finalizedRequest2 + " to client as it is not valid!\n" + serverHistoryTextView.getText().toString());
                            }
                        });
                    }
                }
            }
            socket.close();
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        }
    }
}
