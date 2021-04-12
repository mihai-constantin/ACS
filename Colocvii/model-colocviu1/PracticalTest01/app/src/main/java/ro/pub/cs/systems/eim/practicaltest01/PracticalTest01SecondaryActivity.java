package ro.pub.cs.systems.eim.practicaltest01;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class PracticalTest01SecondaryActivity extends AppCompatActivity {

    TextView counter_text_view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_practical_test01_secondary);

        counter_text_view = findViewById(R.id.counter_text_view);

        Intent intent = getIntent();
        if (intent != null) {
            String counter = intent.getStringExtra("ro.pub.cs.systems.eim.practicaltest01.COUNTER_KEY");
            if (counter != null) {
                counter_text_view.setText(counter);
            } else {
                Toast.makeText(this, getResources().getString(R.string.counter), Toast.LENGTH_LONG).show();
            }
        }

        Button ok_button = findViewById(R.id.ok_button);
        ok_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setResult(Activity.RESULT_OK, new Intent());
                finish();
            }
        });

        Button cancel_button = findViewById(R.id.cancel_button);
        cancel_button.setOnClickListener(new View.OnClickListener() {
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
            case Constants.PRACTICAL_TEST_01_MAIN_ACTIVITY_REQUEST_CODE:
                setResult(resultCode, new Intent());
                finish();
                break;
        }

    }
}