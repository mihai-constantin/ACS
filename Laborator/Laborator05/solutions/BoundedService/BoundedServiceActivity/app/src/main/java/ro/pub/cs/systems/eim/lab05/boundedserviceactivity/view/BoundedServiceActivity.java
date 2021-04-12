package ro.pub.cs.systems.eim.lab05.boundedserviceactivity.view;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.sql.Timestamp;

import ro.pub.cs.systems.eim.lab05.boundedserviceactivity.R;
import ro.pub.cs.systems.eim.lab05.boundedserviceactivity.general.Constants;
import ro.pub.cs.systems.eim.lab05.boundedserviceactivity.service.BoundedService;

public class BoundedServiceActivity extends AppCompatActivity {

    public TextView messageFromServiceTextView;
    public Button getMessageFromServiceButton;

    private BoundedService boundedService;
    private int boundedServiceStatus = Constants.SERVICE_STATUS_UNBOUND;

    // TODO: exercise 10e - implement a button click listener for getMessageFromServiceButton
    private GetMessageFromServiceButtonListener getMessageFromServiceButtonListener = new GetMessageFromServiceButtonListener();
    private class GetMessageFromServiceButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            if (boundedService != null && boundedServiceStatus == Constants.SERVICE_STATUS_BOUND) {
                messageFromServiceTextView.setText("[" + new Timestamp(System.currentTimeMillis()) + "] " + boundedService.getMessage() + "\n" + messageFromServiceTextView.getText());
            }
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bounded_service);

        messageFromServiceTextView = (TextView)findViewById(R.id.message_from_service_text_view);
        getMessageFromServiceButton = (Button)findViewById(R.id.get_message_from_service_button);

        // TODO: exercise 10e - set an instance of the button click listener to handle click events
        // for getMessageFromServiceButton
        getMessageFromServiceButton.setOnClickListener(getMessageFromServiceButtonListener);
    }

    @Override
    protected void onStart() {
        super.onStart();
        // TODO: exercise 10d - bind the service through an intent
        Intent intent = new Intent(this, BoundedService.class);
        bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected  void onStop() {
        // TODO: exercise 10d - unbind the service
        if (boundedServiceStatus == Constants.SERVICE_STATUS_BOUND) {
            unbindService(serviceConnection);
            boundedServiceStatus = Constants.SERVICE_STATUS_UNBOUND;
        }
        super.onStop();
    }

    // TODO: exercise 10c - create a ServiceConnection object
    // override methods onServiceConnected() and onServiceDisconnected()
    private ServiceConnection serviceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            BoundedService.BoundedServiceBinder binder = (BoundedService.BoundedServiceBinder)service;
            boundedService = binder.getService();
            boundedServiceStatus = Constants.SERVICE_STATUS_BOUND;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            boundedService = null;
            boundedServiceStatus = Constants.SERVICE_STATUS_UNBOUND;
        }
    };
}
