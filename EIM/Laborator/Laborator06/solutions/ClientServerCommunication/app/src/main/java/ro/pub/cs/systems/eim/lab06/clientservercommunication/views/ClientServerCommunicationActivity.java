package ro.pub.cs.systems.eim.lab06.clientservercommunication.views;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import ro.pub.cs.systems.eim.lab06.clientservercommunication.R;

public class ClientServerCommunicationActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_client_server_communication);

        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.add(R.id.server_frame_layout, new ServerFragment());
        fragmentTransaction.add(R.id.client_frame_layout, new ClientFragment());
        fragmentTransaction.commit();

    }
}
