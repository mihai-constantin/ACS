package ro.pub.cs.systems.eim.practicaltest01;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.TextView;

import ro.pub.cs.systems.eim.practicaltest01.service.ServiceConstants;

public class StartedServiceBroadcastReceiver extends BroadcastReceiver {

    private TextView messageTextView;

    public StartedServiceBroadcastReceiver() {

    }

    public StartedServiceBroadcastReceiver(TextView messageTextView) {
        this.messageTextView = messageTextView;
    }


    @Override
    public void onReceive(Context context, Intent intent) {

        String action = intent.getAction();
        String data = null;
        if (ServiceConstants.ACTION_INTEGER.equals(action)) {
            data = String.valueOf(intent.getIntExtra(ServiceConstants.DATA, -1));
//            Log.d(Constants.SERVICE, data);
        } else if (ServiceConstants.ACTION_STRING.equals(action)) {
            data = intent.getStringExtra(ServiceConstants.DATA);
        } else if (ServiceConstants.ACTION_MG.equals(action)) {
            data = intent.getStringExtra(ServiceConstants.DATA);
        }

        if (messageTextView != null) {
            messageTextView.setText(messageTextView.getText().toString() + "\n" + data);
        }

        // restart the activity through an intent
        // if the messageTextView is not available
        Intent startedServiceActivityIntent = new Intent(context, PracticalTest01MainActivity.class);
        startedServiceActivityIntent.putExtra(Constants.MESSAGE, data);
        startedServiceActivityIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK|Intent.FLAG_ACTIVITY_SINGLE_TOP);
        context.startActivity(startedServiceActivityIntent);
    }
}
