package ro.pub.cs.systems.eim.practicaltest01var03;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class PracticalTest01Var03SecondaryActivity extends AppCompatActivity {

    private TextView result_text_view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_practical_test01_var03_secondary);

        result_text_view = findViewById(R.id.result_text_view_second_activity);

        Intent intent = getIntent();
        if (intent != null) {
            String result = intent.getStringExtra("ro.pub.cs.systems.eim.practicaltest01var03.RESULT_TEXT_VIEW");
            if (result != null) {
                result_text_view.setText(result);
            } else {
                Toast.makeText(this, getResources().getString(R.string.result), Toast.LENGTH_LONG).show();
            }
        }

        Button correct_button = findViewById(R.id.correct_button);
        correct_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setResult(Activity.RESULT_OK, new Intent());
                finish();
            }
        });

        Button incorrect_button = findViewById(R.id.incorrect_button);
        incorrect_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setResult(Activity.RESULT_CANCELED, new Intent());
                finish();
            }
        });

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case Constants.PRACTICAL_TEST_01_VAR_03_MAIN_ACTIVITY_REQUEST_CODE:
                setResult(resultCode, new Intent());
                finish();
                break;
        }
    }
}