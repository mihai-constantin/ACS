package ro.pub.cs.systems.eim.practicaltest01var03;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import ro.pub.cs.systems.eim.practicaltest01var03.service.ServiceConstants;

public class StartedServiceBroadcastReceiver extends BroadcastReceiver {

    public StartedServiceBroadcastReceiver() {

    }


    @Override
    public void onReceive(Context context, Intent intent) {

        String action = intent.getAction();
        String data = null;
        if (ServiceConstants.ACTION_SUM.equals(action)) {
            data = intent.getStringExtra(ServiceConstants.DATA);
            Log.d(ServiceConstants.SERVICE, "[service] sum: " + data);
        } else if (ServiceConstants.ACTION_DIF.equals(action)) {
            data = intent.getStringExtra(ServiceConstants.DATA);
            Log.d(ServiceConstants.SERVICE, "[service] diff: " + data);
        }

        // restart the activity through an intent
        // if the messageTextView is not available
        Intent startedServiceActivityIntent = new Intent(context, PracticalTest01Var03MainActivity.class);
        startedServiceActivityIntent.putExtra(Constants.MESSAGE, data);
        startedServiceActivityIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK|Intent.FLAG_ACTIVITY_SINGLE_TOP);
        context.startActivity(startedServiceActivityIntent);
    }
}
