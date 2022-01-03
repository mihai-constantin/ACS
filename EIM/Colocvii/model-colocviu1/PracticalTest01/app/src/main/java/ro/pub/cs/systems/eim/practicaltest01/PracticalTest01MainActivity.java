package ro.pub.cs.systems.eim.practicaltest01;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import ro.pub.cs.systems.eim.practicaltest01.service.ServiceConstants;

public class PracticalTest01MainActivity extends AppCompatActivity {

    private TextView messageTextView;

    private ViewClickListener mViewClickListener = new ViewClickListener();

    private Intent serviceIntent;

    private int started = 0;

    private StartedServiceBroadcastReceiver startedServiceBroadcastReceiver;
    private IntentFilter startedServiceIntentFilter;
    private static final int THRESHOLD = 5;

    private class ViewClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {

            Button press_me_button = findViewById(R.id.press_me_button);
            Button press_me_too_button = findViewById(R.id.press_me_too_button);
            Button navigate_to_second_activity = findViewById(R.id.navigate_to_second_activity_button);

            press_me_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
                    EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);

                    Integer counter = Integer.valueOf(press_me_edit_text.getText().toString());
                    String new_counter = String.valueOf(counter + 1);
                    press_me_edit_text.setText(new_counter);

                    if (started == 0 && counter + 1 + Integer.valueOf(press_me_too_edit_text.getText().toString()) > THRESHOLD) {
                        started = 1;
                        serviceIntent.putExtra("ro.pub.cs.systems.eim.practicaltest01.PRESS_ME", press_me_edit_text.getText().toString());
                        serviceIntent.putExtra("ro.pub.cs.systems.eim.practicaltest01.PRESS_ME_TOO", press_me_too_edit_text.getText().toString());
                        startService(serviceIntent);
                    }
                }
            });


            press_me_too_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
                    EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);
                    Integer counter = Integer.valueOf(press_me_too_edit_text.getText().toString());
                    String new_counter = String.valueOf(counter + 1);
                    press_me_too_edit_text.setText(new_counter);

                    if (started == 0 && counter + 1 + Integer.valueOf(press_me_edit_text.getText().toString()) > THRESHOLD) {
                        started = 1;
                        serviceIntent.putExtra("ro.pub.cs.systems.eim.practicaltest01.PRESS_ME", press_me_edit_text.getText().toString());
                        serviceIntent.putExtra("ro.pub.cs.systems.eim.practicaltest01.PRESS_ME_TOO", press_me_too_edit_text.getText().toString());
                        startService(serviceIntent);
                    }
                }
            });

            navigate_to_second_activity.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
                    EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);

                    Intent intent = new Intent("ro.pub.cs.systems.eim.practicaltest01.intent.action.PracticalTest01SecondaryActivity");
                    Integer counter1 = Integer.valueOf(press_me_edit_text.getText().toString());
                    Integer counter2 = Integer.valueOf(press_me_too_edit_text.getText().toString());
                    intent.putExtra("ro.pub.cs.systems.eim.practicaltest01.COUNTER_KEY", String.valueOf(counter1 + counter2));
                    startActivityForResult(intent, Constants.PRACTICAL_TEST_01_MAIN_ACTIVITY_REQUEST_CODE);
                }
            });

        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_practical_test01_main);

        messageTextView = (TextView)findViewById(R.id.message_text_view);

        // start the service
        serviceIntent = new Intent();
        serviceIntent.setComponent(new ComponentName("ro.pub.cs.systems.eim.practicaltest01", "ro.pub.cs.systems.eim.practicaltest01.service.PracticalTest01Service"));

        // create an instance of the StartedServiceBroadcastReceiver broadcast receiver
        startedServiceBroadcastReceiver = new StartedServiceBroadcastReceiver(messageTextView);

        // create an instance of an IntentFilter
        // with all available actions contained within the broadcast intents sent by the service
        startedServiceIntentFilter = new IntentFilter();
        startedServiceIntentFilter.addAction(ServiceConstants.ACTION_INTEGER);
        startedServiceIntentFilter.addAction(ServiceConstants.ACTION_STRING);
        startedServiceIntentFilter.addAction(ServiceConstants.ACTION_MG);

        Button press_me_button = findViewById(R.id.press_me_button);
        Button press_me_too_button = findViewById(R.id.press_me_too_button);

        press_me_button.setOnClickListener(mViewClickListener);
        press_me_too_button.setOnClickListener(mViewClickListener);

        // save values for edit textst
        if (savedInstanceState == null) {
            Log.d(Constants.TAG, "onCreate() method was invoked without a previous state");
        } else {
            Log.d(Constants.TAG, "onCreate() method was invoked with a previous state");

            EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
            EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);

            if (savedInstanceState.getString(Constants.PRESS_ME_EDIT_TEXT) != null) {
                press_me_edit_text.setText(savedInstanceState.getString(Constants.PRESS_ME_EDIT_TEXT));
            }
            if (savedInstanceState.getString(Constants.PRESS_ME_TOO_EDIT_TEXT) != null) {
                press_me_too_edit_text.setText(savedInstanceState.getString(Constants.PRESS_ME_TOO_EDIT_TEXT));
            }
        }

    }

    @Override
    protected void onResume() {
        super.onResume();
        registerReceiver(startedServiceBroadcastReceiver, startedServiceIntentFilter);
    }

    @Override
    protected void onPause() {
        unregisterReceiver(startedServiceBroadcastReceiver);
        super.onPause();
    }

    @Override
    protected void onDestroy() {
        Intent intent = new Intent();
        intent.setComponent(new ComponentName("ro.pub.cs.systems.eim.practicaltest01", "ro.pub.cs.systems.eim.practicaltest01.service.PracticalTest01Service"));
        stopService(intent);

        super.onDestroy();
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);

        String data = intent.getStringExtra(Constants.MESSAGE);
//        Log.d(Constants.SERVICE, data);
        messageTextView.setText(messageTextView.getText().toString() + "\n" + data);
    }


    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);

        EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
        EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);

        outState.putString(Constants.PRESS_ME_EDIT_TEXT, press_me_edit_text.getText().toString());
        outState.putString(Constants.PRESS_ME_TOO_EDIT_TEXT, press_me_too_edit_text.getText().toString());
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
        EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);

        if (savedInstanceState.getString(Constants.PRESS_ME_EDIT_TEXT) != null) {
            press_me_edit_text.setText(savedInstanceState.getString(Constants.PRESS_ME_EDIT_TEXT));
        }
        if (savedInstanceState.getString(Constants.PRESS_ME_TOO_EDIT_TEXT) != null) {
            press_me_too_edit_text.setText(savedInstanceState.getString(Constants.PRESS_ME_TOO_EDIT_TEXT));
        }

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == Activity.RESULT_OK) {
            Toast.makeText(this, "OK button was pressed [" + resultCode+ "]", Toast.LENGTH_LONG).show();
        } else {
            Toast.makeText(this, "CANCEL button was pressed [" + resultCode+ "]", Toast.LENGTH_LONG).show();
        }

    }
}