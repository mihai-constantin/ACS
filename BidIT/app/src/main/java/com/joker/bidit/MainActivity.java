package com.joker.bidit;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.joker.bidit.login.Authentication;
import com.joker.bidit.utils.EmailHelper;

public class MainActivity extends AppCompatActivity {

    private EditText mEditTextEmail;
    private EditText mEditTextPhone;
    private CheckBox mCheckBoxAccept;

    private Authentication mAuthentication;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        mAuthentication = new Authentication();
        initView();
    }

    // get the views from the layout based on an unique id defined in the xml file
    private void initView() {
        mEditTextEmail = findViewById(R.id.edittext_email);
        mEditTextPhone = findViewById(R.id.edittext_phone);
        mCheckBoxAccept = findViewById(R.id.checkbox_accept);
    }

    // validate the content from the email EditText
    private boolean isEmailValid() {
        String email = mEditTextEmail.getText().toString();
        if (EmailHelper.isEmailValid(email)) {
            mAuthentication.setEmail(email);
            return true;
        } else {
            mEditTextEmail.setError(getResources().getString(R.string.error_email_input));
            return false;
        }
    }

    // validate the content from the phone EditText
    private boolean isPhoneValid() {
        String phone = mEditTextPhone.getText().toString();
        if (phone != null && !phone.isEmpty()) {
            mAuthentication.setPhone(phone);
            return true;
        } else {
            mEditTextPhone.setError(getResources().getString(R.string.error_phone_input));
            return false;
        }
    }

    // check if the checkbox is checked
    private boolean isAccepted() {
        if (mCheckBoxAccept.isChecked()) {
            mAuthentication.setAccepted(true);
            return true;
        } else {
            Toast.makeText(MainActivity.this, getResources().getString(R.string
                    .error_is_accepted_input), Toast.LENGTH_SHORT).show();
            return false;
        }
    }
    public void recyclerViewOnClick(View view) {
        if (isEmailValid() && isPhoneValid() && isAccepted()) {
            Toast.makeText(MainActivity.this, mAuthentication.toString(),
                    Toast.LENGTH_LONG).show();
            startActivity(new Intent(MainActivity.this, com.joker.bidit.dashboard.ProductsActivity.class));
        }
    }

}
