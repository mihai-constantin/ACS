package ro.pub.cs.systems.eim.lab05.boundedserviceactivity.view;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab05.boundedserviceactivity.R;
import ro.pub.cs.systems.eim.lab05.boundedserviceactivity.general.Constants;
import ro.pub.cs.systems.eim.lab05.boundedserviceactivity.service.BoundedService;

public class BoundedServiceActivity extends AppCompatActivity {

    public TextView messageFromServiceTextView;
    public Button getMessageFromServiceButton;

    private BoundedService boundedService;
    private int boundedServiceStatus = Constants.SERVICE_STATUS_UNBOUND;

    // TODO: exercise 10e - implement a button click listener for getMessageFromServiceButton

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bounded_service);

        messageFromServiceTextView = (TextView)findViewById(R.id.message_from_service_text_view);
        getMessageFromServiceButton = (Button)findViewById(R.id.get_message_from_service_button);

        // TODO: exercise 10e - set an instance of the button click listener to handle click events
        // for getMessageFromServiceButton
    }

    @Override
    protected void onStart() {
        super.onStart();
        // TODO: exercise 10d - bind the service through an intent
    }

    @Override
    protected  void onStop() {
        // TODO: exercise 10d - unbind the service
        super.onStop();
    }

    // TODO: exercise 10c - create a ServiceConnection object
    // override methods onServiceConnected() and onServiceDisconnected()
}
