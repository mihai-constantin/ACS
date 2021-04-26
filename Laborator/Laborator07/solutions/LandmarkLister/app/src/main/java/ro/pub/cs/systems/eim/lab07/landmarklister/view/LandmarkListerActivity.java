package ro.pub.cs.systems.eim.lab07.landmarklister.view;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import ro.pub.cs.systems.eim.lab07.landmarklister.R;
import ro.pub.cs.systems.eim.lab07.landmarklister.general.Constants;
import ro.pub.cs.systems.eim.lab07.landmarklister.network.LandmarkListerAsyncTask;

public class LandmarkListerActivity extends AppCompatActivity {

    private EditText northEditText, southEditText, eastEditText, westEditText;
    private Button showResultsButton;
    private ListView landmarksListView;

    private ShowResultsButtonClickListener showResultsButtonClickListener = new ShowResultsButtonClickListener();
    private class ShowResultsButtonClickListener implements Button.OnClickListener {

        @Override
        public void onClick(View view) {
            String northString = northEditText.getText().toString();
            if (northString == null || northString.isEmpty()) {
                Toast.makeText(getApplication(), Constants.MISSING_INFORMATION_ERROR_MESSAGE, Toast.LENGTH_LONG).show();
                return;
            }
            String southString = southEditText.getText().toString();
            if (southString == null || southString.isEmpty()) {
                Toast.makeText(getApplication(), Constants.MISSING_INFORMATION_ERROR_MESSAGE, Toast.LENGTH_LONG).show();
                return;
            }
            String eastString = eastEditText.getText().toString();
            if (eastString == null || eastString.isEmpty()) {
                Toast.makeText(getApplication(), Constants.MISSING_INFORMATION_ERROR_MESSAGE, Toast.LENGTH_LONG).show();
                return;
            }
            String westString = westEditText.getText().toString();
            if (westString == null || westString.isEmpty()) {
                Toast.makeText(getApplication(), Constants.MISSING_INFORMATION_ERROR_MESSAGE, Toast.LENGTH_LONG).show();
                return;
            }
            new LandmarkListerAsyncTask(landmarksListView).execute(northString, southString, eastString, westString);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_landmark_lister);

        northEditText = (EditText)findViewById(R.id.north_edit_text);
        southEditText = (EditText)findViewById(R.id.south_edit_text);
        eastEditText = (EditText)findViewById(R.id.east_edit_text);
        westEditText = (EditText)findViewById(R.id.west_edit_text);

        showResultsButton = (Button)findViewById(R.id.show_results_button);
        showResultsButton.setOnClickListener(showResultsButtonClickListener);

        landmarksListView = (ListView)findViewById(R.id.landmarks_list_view);
    }
}
