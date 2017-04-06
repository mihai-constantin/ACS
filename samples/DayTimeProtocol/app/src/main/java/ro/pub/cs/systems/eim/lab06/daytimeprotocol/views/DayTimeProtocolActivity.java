package ro.pub.cs.systems.eim.lab06.daytimeprotocol.views;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab06.daytimeprotocol.R;
import ro.pub.cs.systems.eim.lab06.daytimeprotocol.network.NISTCommunicationAsyncTask;

public class DayTimeProtocolActivity extends AppCompatActivity {

    private Button getInformationButton;
    private TextView dayTimeProtocolTextView;

    private ButtonClickListener buttonClickListener = new ButtonClickListener();
    private class ButtonClickListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            NISTCommunicationAsyncTask nistCommunicationAsyncTask = new NISTCommunicationAsyncTask(dayTimeProtocolTextView);
            nistCommunicationAsyncTask.execute();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_day_time_protocol);

        getInformationButton = (Button)findViewById(R.id.get_information_button);
        getInformationButton.setOnClickListener(buttonClickListener);

        dayTimeProtocolTextView = (TextView)findViewById(R.id.daytime_protocol_text_view);
    }
}
