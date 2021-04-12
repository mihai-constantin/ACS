package ro.pub.cs.systems.eim.practicaltest01var03;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


public class PracticalTest01Var03MainActivity extends AppCompatActivity {

    private TextView result_text_view;


    private ViewClickListener mViewClickListener = new ViewClickListener();

    private class ViewClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {

            Button plus_button = findViewById(R.id.plus_button);
            Button minus_button = findViewById(R.id.minus_button);
            Button navigate_to_second_activity = findViewById(R.id.navigate_to_second_activity_button);

            plus_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText first_number_edit_text = findViewById(R.id.edit_text_first_number);
                    EditText second_number_edit_text = findViewById(R.id.edit_text_second_number);

                    String first_number = first_number_edit_text.getText().toString();
                    String second_number = second_number_edit_text.getText().toString();

                    if (first_number.matches("[0-9]+") && second_number.matches("[0-9]+")) {
                        String result = String.valueOf(Integer.valueOf(first_number) + Integer.valueOf(second_number));
                        result_text_view.setText(first_number + "+" + second_number + "=" + result);
                    } else {
                        Toast.makeText(getApplication(), getResources().getString(R.string.plus_error), Toast.LENGTH_LONG).show();
                    }
                }
            });

            minus_button.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    EditText first_number_edit_text = findViewById(R.id.edit_text_first_number);
                    EditText second_number_edit_text = findViewById(R.id.edit_text_second_number);

                    String first_number = first_number_edit_text.getText().toString();
                    String second_number = second_number_edit_text.getText().toString();

                    if (first_number.matches("[0-9]+") && second_number.matches("[0-9]+")) {
                        String result = String.valueOf(Integer.valueOf(first_number) - Integer.valueOf(second_number));
                        result_text_view.setText(first_number + "-" + second_number + "=" + result);
                    } else {
                        Toast.makeText(getApplication(), getResources().getString(R.string.minus_error), Toast.LENGTH_LONG).show();
                    }
                }
            });

            navigate_to_second_activity.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    TextView result_text_view = findViewById(R.id.result_text_view);
                    Intent intent = new Intent("ro.pub.cs.systems.eim.practicaltest01var03.intent.action.PracticalTest01Var03SecondaryActivity");
                    intent.putExtra("ro.pub.cs.systems.eim.practicaltest01var03.RESULT_TEXT_VIEW", result_text_view.getText().toString());
                    startActivityForResult(intent, Constants.PRACTICAL_TEST_01_VAR_03_MAIN_ACTIVITY_REQUEST_CODE);
                }
            });
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_practical_test01_var03_main);

        result_text_view = findViewById(R.id.result_text_view);

        Button plus_button = findViewById(R.id.plus_button);
        Button minus_button = findViewById(R.id.minus_button);

        plus_button.setOnClickListener(mViewClickListener);
        minus_button.setOnClickListener(mViewClickListener);

        // save values for edit texts
        if (savedInstanceState == null) {
            Log.d(Constants.TAG, "onCreate() method was invoked without a previous state");
        } else {
            Log.d(Constants.TAG, "onCreate() method was invoked with a previous state");

            EditText first_number_edit_text = findViewById(R.id.edit_text_first_number);
            EditText second_number_edit_text = findViewById(R.id.edit_text_second_number);
            TextView result_text_view = findViewById(R.id.result_text_view);

            if (savedInstanceState.getString(Constants.FIRST_NUMBER_EDIT_TEXT) != null) {
                first_number_edit_text.setText(savedInstanceState.getString(Constants.FIRST_NUMBER_EDIT_TEXT));
            }
            if (savedInstanceState.getString(Constants.SECOND_NUMBER_EDIT_TEXT) != null) {
                second_number_edit_text.setText(savedInstanceState.getString(Constants.SECOND_NUMBER_EDIT_TEXT));
            }
            if (savedInstanceState.getString(Constants.RESULT_TEXT_VIEW) != null) {
                result_text_view.setText(savedInstanceState.getString(Constants.RESULT_TEXT_VIEW));
            }
        }

    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        super.onSaveInstanceState(outState);

        EditText first_number_edit_text = findViewById(R.id.edit_text_first_number);
        EditText second_number_edit_text = findViewById(R.id.edit_text_second_number);
        TextView result_text_view = findViewById(R.id.result_text_view);

        outState.putString(Constants.FIRST_NUMBER_EDIT_TEXT, first_number_edit_text.getText().toString());
        outState.putString(Constants.SECOND_NUMBER_EDIT_TEXT, second_number_edit_text.getText().toString());
        outState.putString(Constants.RESULT_TEXT_VIEW, result_text_view.getText().toString());
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);

        EditText first_number_edit_text = findViewById(R.id.edit_text_first_number);
        EditText second_number_edit_text = findViewById(R.id.edit_text_second_number);
        TextView result_text_view = findViewById(R.id.result_text_view);

        if (savedInstanceState.getString(Constants.FIRST_NUMBER_EDIT_TEXT) != null) {
            first_number_edit_text.setText(savedInstanceState.getString(Constants.FIRST_NUMBER_EDIT_TEXT));
        }
        if (savedInstanceState.getString(Constants.SECOND_NUMBER_EDIT_TEXT) != null) {
            second_number_edit_text.setText(savedInstanceState.getString(Constants.SECOND_NUMBER_EDIT_TEXT));
        }
        if (savedInstanceState.getString(Constants.RESULT_TEXT_VIEW) != null) {
            result_text_view.setText(savedInstanceState.getString(Constants.RESULT_TEXT_VIEW));
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == Activity.RESULT_OK) {
            Toast.makeText(this, "Correct button was pressed [" + resultCode+ "]", Toast.LENGTH_LONG).show();
        } else {
            Toast.makeText(this, "Incorrect button was pressed [" + resultCode+ "]", Toast.LENGTH_LONG).show();
        }

    }

}