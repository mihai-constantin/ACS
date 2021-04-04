package ro.pub.cs.systems.eim.lab05.startedserviceactivity.view;

import android.content.IntentFilter;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab05.startedserviceactivity.R;

public class StartedServiceActivity extends AppCompatActivity {

    private TextView messageTextView;
    private StartedServiceBroadcastReceiver startedServiceBroadcastReceiver;
    private IntentFilter startedServiceIntentFilter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_started_service);

        messageTextView = (TextView)findViewById(R.id.message_text_view);

        // TODO: exercise 6 - start the service

        // TODO: exercise 8a - create an instance of the StartedServiceBroadcastReceiver broadcast receiver

        // TODO: exercise 8b - create an instance of an IntentFilter
        // with all available actions contained within the broadcast intents sent by the service

    }

    @Override
    protected void onResume() {
        super.onResume();

        // TODO: exercise 8c - register the broadcast receiver with the corresponding intent filter
    }

    @Override
    protected void onPause() {
        // TODO: exercise 8c - unregister the broadcast receiver

        super.onPause();
    }

    @Override
    protected void onDestroy() {
        // TODO: exercise 8d - stop the service

        super.onDestroy();
    }

    // TODO: exercise 9 - implement the onNewIntent callback method
    // get the message from the extra field of the intent
    // and display it in the messageTextView

}
