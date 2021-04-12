package ro.pub.cs.systems.eim.lab04.contactsmanager;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;

public class PhoneDialer extends AppCompatActivity {

    private static final int PERMISSION_REQUEST_CALL_PHONE = 1;

    private ViewClickListener mViewClickListener = new ViewClickListener();

    private class ViewClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {

            EditText phoneNumberEditText = (EditText) findViewById(R.id.phoneNumberEditText);

            Button button0 = (Button) findViewById(R.id.button0);
            button0.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(phoneNumber + "0");
            });

            Button button1 = (Button) findViewById(R.id.button1);
            button1.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(phoneNumber + "1");
            });

            Button button2 = (Button) findViewById(R.id.button2);
            button2.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s2", phoneNumber));
            });

            Button button3 = (Button) findViewById(R.id.button3);
            button3.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s3", phoneNumber));
            });

            Button button4 = (Button) findViewById(R.id.button4);
            button4.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s4", phoneNumber));
            });

            Button button5 = (Button) findViewById(R.id.button5);
            button5.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s5", phoneNumber));
            });

            Button button6 = (Button) findViewById(R.id.button6);
            button6.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s6", phoneNumber));
            });

            Button button7 = (Button) findViewById(R.id.button7);
            button7.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s7", phoneNumber));
            });

            Button button8 = (Button) findViewById(R.id.button8);
            button8.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s8", phoneNumber));
            });

            Button button9 = (Button) findViewById(R.id.button9);
            button9.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s9", phoneNumber));
            });

            Button button_star = (Button) findViewById(R.id.button_star);
            button_star.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s*", phoneNumber));
            });

            Button button_hash = (Button) findViewById(R.id.button_hash);
            button_hash.setOnClickListener(view1 -> {
                String phoneNumber = phoneNumberEditText.getText().toString();
                phoneNumberEditText.setText(String.format("%s#", phoneNumber));
            });

            ImageButton backspaceImageButton = (ImageButton) findViewById(R.id.backspaceImageButton);
            backspaceImageButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    String phoneNumber = phoneNumberEditText.getText().toString();
                    if (phoneNumber != null && phoneNumber.length() > 0) {
                        phoneNumberEditText.setText(phoneNumber.substring(0, phoneNumber.length() - 1));
                    }
                }
            });

            ImageButton callImageButton = (ImageButton) findViewById(R.id.callImageButton);
            callImageButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent intent = new Intent(Intent.ACTION_CALL);
                    intent.setData(Uri.parse("tel:" + phoneNumberEditText.getText().toString()));
                    if (ActivityCompat.checkSelfPermission(PhoneDialer.this, Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED) {
                        // TODO: Consider calling
                        //    ActivityCompat#requestPermissions
                        // here to request the missing permissions, and then overriding
                        //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
                        //                                          int[] grantResults)
                        // to handle the case where the user grants the permission. See the documentation
                        // for ActivityCompat#requestPermissions for more details.
                        ActivityCompat.requestPermissions(
                                PhoneDialer.this,
                                new String[]{Manifest.permission.CALL_PHONE},
                                PERMISSION_REQUEST_CALL_PHONE);
                        return;
                    }
                    startActivity(intent);
                }
            });

            ImageButton hangupImageButton = (ImageButton) findViewById(R.id.hangupImageButton);
            hangupImageButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    finish();
                }
            });

            ImageButton contactsImageButton = (ImageButton) findViewById(R.id.contactsImageButton);
            contactsImageButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    String phoneNumber = phoneNumberEditText.getText().toString();
                    if (phoneNumber != null && phoneNumber.length() > 0) {
                        Intent intent = new Intent("ro.pub.cs.systems.eim.lab04.contactsmanager.intent.action.MainActivity");
                        intent.putExtra("ro.pub.cs.systems.eim.lab04.contactsmanager.PHONE_NUMBER_KEY", phoneNumber);
                        startActivityForResult(intent, Constants.CONTACTS_MANAGER_REQUEST_CODE);
                    } else {
                        Toast.makeText(getApplication(), getResources().getString(R.string.phone_error), Toast.LENGTH_LONG).show();
                    }
                }
            });
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_phone_dialer);

        Button button0 = (Button) findViewById(R.id.button0);
        Button button1 = (Button) findViewById(R.id.button1);
        Button button2 = (Button) findViewById(R.id.button2);
        Button button3 = (Button) findViewById(R.id.button3);
        Button button4 = (Button) findViewById(R.id.button4);
        Button button5 = (Button) findViewById(R.id.button5);
        Button button6 = (Button) findViewById(R.id.button6);
        Button button7 = (Button) findViewById(R.id.button7);
        Button button8 = (Button) findViewById(R.id.button8);
        Button button9 = (Button) findViewById(R.id.button9);
        Button button_star = (Button) findViewById(R.id.button_star);
        Button button_hash = (Button) findViewById(R.id.button_hash);
        ImageButton backspaceImageButton = (ImageButton) findViewById(R.id.backspaceImageButton);
        ImageButton callImageButton = (ImageButton) findViewById(R.id.callImageButton);
        ImageButton hangupImageButton = (ImageButton) findViewById(R.id.hangupImageButton);
        ImageButton contactsImageButton = (ImageButton) findViewById(R.id.contactsImageButton);

        button0.setOnClickListener(mViewClickListener);
        button1.setOnClickListener(mViewClickListener);
        button2.setOnClickListener(mViewClickListener);
        button3.setOnClickListener(mViewClickListener);
        button4.setOnClickListener(mViewClickListener);
        button5.setOnClickListener(mViewClickListener);
        button6.setOnClickListener(mViewClickListener);
        button7.setOnClickListener(mViewClickListener);
        button8.setOnClickListener(mViewClickListener);
        button9.setOnClickListener(mViewClickListener);
        button_star.setOnClickListener(mViewClickListener);
        button_hash.setOnClickListener(mViewClickListener);
        backspaceImageButton.setOnClickListener(mViewClickListener);
        callImageButton.setOnClickListener(mViewClickListener);
        hangupImageButton.setOnClickListener(mViewClickListener);
        contactsImageButton.setOnClickListener(mViewClickListener);
    }
}