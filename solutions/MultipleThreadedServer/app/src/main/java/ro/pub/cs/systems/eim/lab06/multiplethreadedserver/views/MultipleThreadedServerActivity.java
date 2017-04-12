package ro.pub.cs.systems.eim.lab06.multiplethreadedserver.views;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.EditText;

import ro.pub.cs.systems.eim.lab06.multiplethreadedserver.R;
import ro.pub.cs.systems.eim.lab06.multiplethreadedserver.general.Constants;
import ro.pub.cs.systems.eim.lab06.multiplethreadedserver.network.ServerThread;

public class MultipleThreadedServerActivity extends AppCompatActivity {

    private EditText serverTextEditText;

    private ServerThread serverThread;

    private ServerTextContentWatcher serverTextContentWatcher = new ServerTextContentWatcher();
    private class ServerTextContentWatcher implements TextWatcher {

        @Override
        public void beforeTextChanged(CharSequence charSequence, int start, int count, int after) {}

        @Override
        public void onTextChanged(CharSequence charSequence, int start, int before, int count) {
            Log.v(Constants.TAG, "Text changed in edit text: " + charSequence.toString());
            if (Constants.SERVER_START.equals(charSequence.toString())) {
                serverThread = new ServerThread(serverTextEditText);
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
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_multiple_threaded_server);

        serverTextEditText = (EditText)findViewById(R.id.server_text_edit_text);
        serverTextEditText.addTextChangedListener(serverTextContentWatcher);
    }

    @Override
    protected void onDestroy() {
        if (serverThread != null) {
            serverThread.stopServer();
        }
        super.onDestroy();
    }
}
