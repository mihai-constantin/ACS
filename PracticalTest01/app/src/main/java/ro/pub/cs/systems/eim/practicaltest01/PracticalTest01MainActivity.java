package ro.pub.cs.systems.eim.practicaltest01;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class PracticalTest01MainActivity extends AppCompatActivity {


    private ViewClickListener mViewClickListener = new ViewClickListener();

    private class ViewClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {

            Button press_me_button = findViewById(R.id.press_me_button);
            Button press_me_too_button = findViewById(R.id.press_me_too_button);


            press_me_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText press_me_edit_text = findViewById(R.id.press_me_edit_text);
                    Integer counter = Integer.valueOf(press_me_edit_text.getText().toString());
                    String new_counter = String.valueOf(counter + 1);
                    press_me_edit_text.setText(new_counter);
                }
            });


            press_me_too_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText press_me_too_edit_text = findViewById(R.id.press_me_too_edit_text);
                    Integer counter = Integer.valueOf(press_me_too_edit_text.getText().toString());
                    String new_counter = String.valueOf(counter + 1);
                    press_me_too_edit_text.setText(new_counter);
                }
            });

        }
    }





    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_practical_test01_main);

        Button press_me_button = findViewById(R.id.press_me_button);
        Button press_me_too_button = findViewById(R.id.press_me_too_button);

        press_me_button.setOnClickListener(mViewClickListener);
        press_me_too_button.setOnClickListener(mViewClickListener);

        // save values for edit texts
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
}