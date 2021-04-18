package ro.pub.cs.systems.eim.lab06.pheasantgame.view;

import android.app.Fragment;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import ro.pub.cs.systems.eim.lab06.pheasantgame.R;
import ro.pub.cs.systems.eim.lab06.pheasantgame.general.Constants;
import ro.pub.cs.systems.eim.lab06.pheasantgame.network.ClientCommunicationThread;

public class ClientFragment extends Fragment {

    private Socket socket;

    private Handler handler;

    private EditText wordEditText;
    private Button sendButton;
    private TextView clientHistoryTextView;

    private ButtonClickListener buttonClickListener = new ButtonClickListener();
    private class ButtonClickListener implements Button.OnClickListener {

        @Override
        public void onClick(View view) {
            ClientCommunicationThread clientCommunicationThread = new ClientCommunicationThread(socket, getActivity(), handler, wordEditText, sendButton, clientHistoryTextView);
            clientCommunicationThread.start();
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle state) {
        return inflater.inflate(R.layout.fragment_client, parent, false);
    }

    @Override
    public void onActivityCreated(Bundle state) {
        super.onActivityCreated(state);

        new Thread(new Runnable() {
            @Override
            public void run() {
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
        }).start();

        handler = new Handler();

        wordEditText = (EditText)getActivity().findViewById(R.id.word_edit_text);
        sendButton = (Button)getActivity().findViewById(R.id.send_button);
        sendButton.setOnClickListener(buttonClickListener);
        clientHistoryTextView = (TextView)getActivity().findViewById(R.id.client_history_text_view);
    }

}
