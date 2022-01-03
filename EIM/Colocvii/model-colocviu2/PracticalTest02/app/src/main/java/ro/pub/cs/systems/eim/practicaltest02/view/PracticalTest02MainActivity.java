package ro.pub.cs.systems.eim.practicaltest02.view;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import ro.pub.cs.systems.eim.practicaltest02.R;
import ro.pub.cs.systems.eim.practicaltest02.general.Constants;
import ro.pub.cs.systems.eim.practicaltest02.network.ClientThread;
import ro.pub.cs.systems.eim.practicaltest02.network.ServerThread;

public class PracticalTest02MainActivity extends AppCompatActivity {

    // Server widgets
    private EditText serverPortEditText = null;
    private Button serverConnectButton = null;

    // Client widgets
    private EditText clientAddressEditText = null;
    private EditText clientPortEditText = null;
    private EditText clientCityEditText = null;
    private Spinner informationTypeSpinner = null;
    private Button getWeatherForecastButton = null;
    private TextView weatherForecastTextView = null;

    // Threads
    private ServerThread serverThread = null;
    private ClientThread clientThread = null;

    private ServerConnectButtonListener serverConnectButtonListener = new ServerConnectButtonListener();
    private class ServerConnectButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            String serverPort = serverPortEditText.getText().toString();
            if (serverPort == null || serverPort.isEmpty()) {
                Toast.makeText(getApplicationContext(), "[MAIN ACTIVITY] Server port cannot be null!", Toast.LENGTH_LONG).show();
                return;
            }
            serverThread = new ServerThread(Integer.parseInt(serverPort));
            if (serverThread.getServerSocket() == null) {
                Log.e(Constants.TAG, "[MAIN ACTIVITY] Could not create server thread!");
                return;
            }
            serverThread.start();
        }
    }

    private ClientGetWeatherButtonListener clientGetWeatherButtonListener = new ClientGetWeatherButtonListener();
    private class ClientGetWeatherButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            String clientAddress = clientAddressEditText.getText().toString();
            String clientPort = clientPortEditText.getText().toString();
            String city = clientCityEditText.getText().toString();
            String informationType = informationTypeSpinner.getSelectedItem().toString();
            if (clientAddress == null || clientAddress.isEmpty() || clientPort == null || clientPort.isEmpty()
                || city == null || city.isEmpty() || informationType == null || informationType.isEmpty()) {
                Toast.makeText(getApplicationContext(), "[MAIN ACTIVITY] Client parameters cannot be null!", Toast.LENGTH_LONG).show();
                return;
            }

            // check serverThread
            if (serverThread == null || !serverThread.isAlive()) {
                Toast.makeText(getApplicationContext(), "[MAIN ACTIVITY] There is no server to connect to!", Toast.LENGTH_LONG).show();
                return;
            }

            weatherForecastTextView.setText(Constants.EMPTY_STRING);

            clientThread = new ClientThread(clientAddress, Integer.parseInt(clientPort), city, informationType, weatherForecastTextView);
            clientThread.start();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i(Constants.TAG, "[MAIN ACTIVITY] onCreate() callback method has been invoked");
        setContentView(R.layout.activity_practical_test02_main);

        // server widgets
        serverPortEditText = findViewById(R.id.portServerEditText);
        serverConnectButton = findViewById(R.id.connectServerButton);
        serverConnectButton.setOnClickListener(serverConnectButtonListener);

        // client widgets
        clientAddressEditText = findViewById(R.id.addressClientEditText);
        clientPortEditText = findViewById(R.id.portClientEditText);
        clientCityEditText = findViewById(R.id.cityClientEditText);
        informationTypeSpinner = findViewById(R.id.information_type_spinner);
        getWeatherForecastButton = findViewById(R.id.getWeatherClientButton);
        getWeatherForecastButton.setOnClickListener(clientGetWeatherButtonListener);
        weatherForecastTextView = findViewById(R.id.weather_forecast_text_view);
    }

    @Override
    protected void onDestroy() {
        Log.i(Constants.TAG, "[MAIN ACTIVITY] onDestroy() callback has been invoked");
        if (serverThread != null) {
            serverThread.stopThread();
        }
        super.onDestroy();
    }
}