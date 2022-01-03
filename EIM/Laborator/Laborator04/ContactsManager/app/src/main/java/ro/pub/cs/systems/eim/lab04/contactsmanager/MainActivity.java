package ro.pub.cs.systems.eim.lab04.contactsmanager;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private EditText nameEditText;
    private EditText phoneEditText;
    private EditText emailEditText;
    private EditText addressEditText;
    private EditText jobTitleEditText;
    private EditText companyEditText;
    private EditText websiteEditText;
    private EditText imEditText;

    private ViewClickListener mViewClickListener = new ViewClickListener();

    private class ViewClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            Button showAdditionFieldsButton = findViewById(R.id.show_addition_filds_button);
            LinearLayout linearLayout2 = findViewById(R.id.linearLayout2);

            showAdditionFieldsButton.setOnClickListener(view1 -> {
                if (showAdditionFieldsButton.getText().toString().equals("SHOW ADDITIONAL FIELDS")) {
                    linearLayout2.setVisibility(View.VISIBLE);
                    showAdditionFieldsButton.setText("HIDE ADDITIONAL FIELDS");
                } else {
                    linearLayout2.setVisibility(View.GONE);
                    showAdditionFieldsButton.setText("SHOW ADDITIONAL FIELDS");
                }
            });

            Button saveButton = findViewById(R.id.save_button);
            saveButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Intent intent = new Intent(ContactsContract.Intents.Insert.ACTION);
                    intent.setType(ContactsContract.RawContacts.CONTENT_TYPE);

                    String name = nameEditText.getText().toString();
                    String phone = phoneEditText.getText().toString();
                    String email = emailEditText.getText().toString();
                    String address = addressEditText.getText().toString();
                    String jobTitle = jobTitleEditText.getText().toString();
                    String company = companyEditText.getText().toString();
                    String website = websiteEditText.getText().toString();
                    String im = imEditText.getText().toString();

                    if (name != null) {
                        intent.putExtra(ContactsContract.Intents.Insert.NAME, name);
                    }
                    if (phone != null) {
                        intent.putExtra(ContactsContract.Intents.Insert.PHONE, phone);
                    }
                    if (email != null) {
                        intent.putExtra(ContactsContract.Intents.Insert.EMAIL, email);
                    }
                    if (address != null) {
                        intent.putExtra(ContactsContract.Intents.Insert.POSTAL, address);
                    }
                    if (jobTitle != null) {
                        intent.putExtra(ContactsContract.Intents.Insert.JOB_TITLE, jobTitle);
                    }
                    if (company != null) {
                        intent.putExtra(ContactsContract.Intents.Insert.COMPANY, company);
                    }

                    ArrayList<ContentValues> contactData = new ArrayList<ContentValues>();
                    if (website != null) {
                        ContentValues websiteRow = new ContentValues();
                        websiteRow.put(ContactsContract.Data.MIMETYPE, ContactsContract.CommonDataKinds.Website.CONTENT_ITEM_TYPE);
                        websiteRow.put(ContactsContract.CommonDataKinds.Website.URL, website);
                        contactData.add(websiteRow);
                    }

                    if (im != null) {
                        ContentValues imRow = new ContentValues();
                        imRow.put(ContactsContract.Data.MIMETYPE, ContactsContract.CommonDataKinds.Im.CONTENT_ITEM_TYPE);
                        imRow.put(ContactsContract.CommonDataKinds.Im.DATA, im);
                        contactData.add(imRow);
                    }
                    intent.putParcelableArrayListExtra(ContactsContract.Intents.Insert.DATA, contactData);
                    startActivityForResult(intent, Constants.CONTACTS_MANAGER_REQUEST_CODE);
                }
            });

            Button cancelButton = findViewById(R.id.cancel_button);
            cancelButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    setResult(Activity.RESULT_CANCELED, new Intent());
                    finish();
                }
            });
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        nameEditText = findViewById(R.id.nameEditText);
        phoneEditText = findViewById(R.id.phoneNumberEditText);
        emailEditText = findViewById(R.id.emailEditText);
        addressEditText = findViewById(R.id.addressEditText);
        jobTitleEditText = findViewById(R.id.jobEditText);
        companyEditText = findViewById(R.id.companyEditText);
        websiteEditText = findViewById(R.id.websiteEditText);
        imEditText = findViewById(R.id.imEditText);

        Button showAdditionFieldsButton = findViewById(R.id.show_addition_filds_button);
        showAdditionFieldsButton.setOnClickListener(mViewClickListener);

        Intent intent = getIntent();
        if (intent != null) {
            String phone = intent.getStringExtra("ro.pub.cs.systems.eim.lab04.contactsmanager.PHONE_NUMBER_KEY");
            if (phone != null) {
                phoneEditText.setText(phone);
            } else {
                Toast.makeText(this, getResources().getString(R.string.phone_error), Toast.LENGTH_LONG).show();
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        switch (requestCode) {
            case Constants.CONTACTS_MANAGER_REQUEST_CODE:
                setResult(resultCode, new Intent());
                finish();
                break;
        }
    }
}