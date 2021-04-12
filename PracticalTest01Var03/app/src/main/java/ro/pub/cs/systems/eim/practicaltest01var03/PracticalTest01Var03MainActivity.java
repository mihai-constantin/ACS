package ro.pub.cs.systems.eim.practicaltest01var03;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
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


    }
}