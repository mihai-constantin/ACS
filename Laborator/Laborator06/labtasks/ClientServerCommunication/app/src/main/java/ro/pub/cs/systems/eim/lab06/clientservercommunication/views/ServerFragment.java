package ro.pub.cs.systems.eim.lab06.clientservercommunication.views;

import android.os.Bundle;
import android.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import ro.pub.cs.systems.eim.lab06.clientservercommunication.R;
import ro.pub.cs.systems.eim.lab06.clientservercommunication.general.Constants;
import ro.pub.cs.systems.eim.lab06.clientservercommunication.network.ServerThread;

public class ServerFragment extends Fragment {

    private EditText serverEditText;

    private ServerThread serverThread;

    private ServerTextContentWatcher serverTextContentWatcher = new ServerTextContentWatcher();
    private class ServerTextContentWatcher implements TextWatcher {

        @Override
        public void beforeTextChanged(CharSequence charSequence, int start, int count, int after) {}

        @Override
        public void onTextChanged(CharSequence charSequence, int start, int before, int count) {
            Log.v(Constants.TAG, "Text changed in edit text: " + charSequence.toString());
            if (Constants.SERVER_START.toString().equals(charSequence.toString())) {
                serverThread = new ServerThread(serverEditText);
                serverThread.startServer();
                Log.v(Constants.TAG, "Starting server...");
            }
            if (Constants.SERVER_STOP.equals(charSequence.toString())) {
                serverThread.stopServer();
                Log.v(Constants.TAG, "Stopping server...");
            }
        }

        @Override
        public void afterTextChanged(Editable editable) {}

    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle state) {
        return inflater.inflate(R.layout.fragment_server, parent, false);
    }

    @Override
    public void onActivityCreated(Bundle state) {
        super.onActivityCreated(state);

        serverEditText = (EditText)getActivity().findViewById(R.id.server_text_edit_text);
        serverEditText.addTextChangedListener(serverTextContentWatcher);
    }

    @Override
    public void onDestroy() {
        if (serverThread != null) {
            serverThread.stopServer();
        }
        super.onDestroy();
    }

}
