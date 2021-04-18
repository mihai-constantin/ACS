package ro.pub.cs.systems.eim.lab06.singlethreadedserver.views;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.EditText;

import ro.pub.cs.systems.eim.lab06.singlethreadedserver.R;
import ro.pub.cs.systems.eim.lab06.singlethreadedserver.general.Constants;
import ro.pub.cs.systems.eim.lab06.singlethreadedserver.network.ServerThread;

public class SingleThreadedServerActivity extends AppCompatActivity {

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
        setContentView(R.layout.activity_single_threaded_server);

        serverTextEditText = (EditText)findViewById(R.id.server_text_edit_text);
        serverTextEditText.addTextChangedListener(serverTextContentWatcher);
    }

    // TODO exercise 5b
    // overwrite method onDestroy() in order to stop the serverThread on it
    // only if it has been initialized before
}
