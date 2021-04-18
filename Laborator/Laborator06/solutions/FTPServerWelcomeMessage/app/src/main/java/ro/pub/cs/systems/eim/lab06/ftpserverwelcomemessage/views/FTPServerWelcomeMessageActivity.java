package ro.pub.cs.systems.eim.lab06.ftpserverwelcomemessage.views;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab06.ftpserverwelcomemessage.R;
import ro.pub.cs.systems.eim.lab06.ftpserverwelcomemessage.network.FTPServerCommunicationAsyncTask;

public class FTPServerWelcomeMessageActivity extends AppCompatActivity {

    private EditText FTPServerAddressEditText;
    private Button displayWelcomeMessageButton;
    private TextView welcomeMessageTextView;

    private ButtonClickListener buttonClickListener = new ButtonClickListener();
    private class ButtonClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            FTPServerCommunicationAsyncTask ftpServerCommunicationAsyncTask = new FTPServerCommunicationAsyncTask(welcomeMessageTextView);
            ftpServerCommunicationAsyncTask.execute(FTPServerAddressEditText.getText().toString());
        }

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ftpserver_welcome_message);

        FTPServerAddressEditText = (EditText)findViewById(R.id.ftp_server_address_edit_text);

        displayWelcomeMessageButton = (Button)findViewById(R.id.display_welcome_message_button);
        displayWelcomeMessageButton.setOnClickListener(buttonClickListener);

        welcomeMessageTextView = (TextView)findViewById(R.id.welcome_message_text_view);
    }
}
