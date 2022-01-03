package ro.pub.cs.systems.eim.lab06.pheasantgame.view;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import ro.pub.cs.systems.eim.lab06.pheasantgame.R;
import ro.pub.cs.systems.eim.lab06.pheasantgame.network.ServerThread;

public class ServerFragment extends Fragment {

    private TextView serverHistoryTextView;

    private ServerThread serverThread;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup parent, Bundle state) {
        return inflater.inflate(R.layout.fragment_server, parent, false);
    }

    @Override
    public void onActivityCreated(Bundle state) {
        super.onActivityCreated(state);

        serverHistoryTextView = (TextView)getActivity().findViewById(R.id.server_history_text_view);

        serverThread = new ServerThread(serverHistoryTextView);
        serverThread.start();
    }

    @Override
    public void onDestroy() {
        if (serverThread != null) {
            serverThread.stopServer();
        }
        super.onDestroy();
    }

}
