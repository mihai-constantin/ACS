package ro.pub.cs.systems.eim.lab05.startedserviceactivity.view;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab05.startedserviceactivity.general.Constants;

public class StartedServiceBroadcastReceiver extends BroadcastReceiver {

    private TextView messageTextView;

    // exercise 9 - default constructor
    public StartedServiceBroadcastReceiver() {

    }

    public StartedServiceBroadcastReceiver(TextView messageTextView) {
        this.messageTextView = messageTextView;
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        // exercise 7 - get the action and the extra information from the intent
        // and set the text on the messageTextView
        String action = intent.getAction();
        String data = null;
        if (Constants.ACTION_STRING.equals(action)) {
            data = intent.getStringExtra(Constants.DATA);
        } else if (Constants.ACTION_INTEGER.equals(action)) {
            data = String.valueOf(intent.getIntExtra(Constants.DATA, -1));
        } else if (Constants.ACTION_ARRAY_LIST.equals(action)) {
            data = intent.getStringArrayListExtra(Constants.DATA).toString();
        }

        if (messageTextView != null) {
            messageTextView.setText(String.format("%s\n%s", messageTextView.getText().toString(), data));
        }

        // exercise 9 - restart the activity through an intent
        // if the messageTextView is not available
        Intent startedServiceActivityIntent = new Intent(context, StartedServiceActivity.class);
        startedServiceActivityIntent.putExtra(Constants.MESSAGE, data);
        startedServiceActivityIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK|Intent.FLAG_ACTIVITY_SINGLE_TOP);
        context.startActivity(startedServiceActivityIntent);
    }
}
