package ro.pub.cs.systems.eim.lab06.pheasantgame.view;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import ro.pub.cs.systems.eim.lab06.pheasantgame.R;

public class PheasantGameActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pheasant_game);

        FragmentManager fragmentManager = getFragmentManager();
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        fragmentTransaction.add(R.id.server_container, new ServerFragment());
        fragmentTransaction.add(R.id.client_container, new ClientFragment());
        fragmentTransaction.commit();
    }
}
