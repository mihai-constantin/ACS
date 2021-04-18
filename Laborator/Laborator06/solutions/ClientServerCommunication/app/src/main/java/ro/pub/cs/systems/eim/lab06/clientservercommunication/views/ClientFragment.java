package ro.pub.cs.systems.eim.lab06.clientservercommunication.views;

import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab06.clientservercommunication.R;
import ro.pub.cs.systems.eim.lab06.clientservercommunication.network.ClientAsyncTask;

public class ClientFragment extends Fragment {

    private EditText serverAddressEditText, serverPortEditText;
    private TextView serverMessageTextView;
    private Button displayMessageButton;

    private ButtonClickListener buttonClickListener = new ButtonClickListener();
    private class ButtonClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            ClientAsyncTask clientAsyncTask = new ClientAsyncTask(serverMessageTextView);
            clientAsyncTask.execute(serverAddressEditText.getText().toString(), serverPortEditText.getText().toString());
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle state) {
        return inflater.inflate(R.layout.fragment_client, parent, false);
    }

    @Override
    public void onActivityCreated(Bundle state) {
        super.onActivityCreated(state);

        serverAddressEditText = (EditText)getActivity().findViewById(R.id.server_address_edit_text);
        serverPortEditText = (EditText)getActivity().findViewById(R.id.server_port_edit_text);
        displayMessageButton = (Button)getActivity().findViewById(R.id.display_message_button);
        displayMessageButton.setOnClickListener(buttonClickListener);
        serverMessageTextView = (TextView)getActivity().findViewById(R.id.server_message_text_view);
    }

}
