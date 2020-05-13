package com.joker.bidit.login;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.google.firebase.storage.UploadTask;
import com.joker.bidit.R;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.navigationDrawer.NavigationDrawerActivity;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class EditProfileActivity extends AppCompatActivity implements View.OnClickListener {

    private FirebaseAuth firebaseAuth;
    private DatabaseReference databaseReference;
    private EditText editTextName;
    private EditText editTextSurname;
    private EditText editTextPhoneNo;
    private Button btnSave;

    private TextView textViewEmailAddress;
    private ImageView profileImageView;
    private FirebaseStorage firebaseStorage;
    private StorageReference storageReference;

    Uri imagePath;

    private static int PICK_IMAGE = 123;

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == PICK_IMAGE && resultCode == RESULT_OK && data.getData() != null) {
            imagePath = data.getData();
            try {
                Bitmap bitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), imagePath);
                profileImageView.setImageBitmap(bitmap);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    public EditProfileActivity() {
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_edit_profile);

        firebaseAuth = FirebaseAuth.getInstance();
        databaseReference = FirebaseDatabase.getInstance().getReference();
        editTextName = findViewById(R.id.EditTextName);
        editTextSurname = findViewById(R.id.EditTextSurname);
        editTextPhoneNo = findViewById(R.id.EditTextPhoneNo);

        btnSave = findViewById(R.id.btnSaveButton);

        FirebaseUser user = firebaseAuth.getCurrentUser();
        btnSave.setOnClickListener(this);
        textViewEmailAddress = findViewById(R.id.textViewEmailAdress);
        textViewEmailAddress.setText(user.getEmail());
        profileImageView = findViewById(R.id.update_imageView);
        firebaseStorage = FirebaseStorage.getInstance();
        storageReference = firebaseStorage.getReference();

        profileImageView.setOnClickListener(v -> {
            Intent profileIntent = new Intent();
            profileIntent.setType("image/*");
            profileIntent.setAction(Intent.ACTION_GET_CONTENT);
            startActivityForResult(Intent.createChooser(profileIntent, "Select Image."), PICK_IMAGE);
        });
    }

    private void userInformation() {
        String name = editTextName.getText().toString().trim();
        String surname = editTextSurname.getText().toString().trim();
        String phoneNo = editTextPhoneNo.getText().toString().trim();
        List<Product> products = new ArrayList<>();
        UserInformation userinformation = UserInformation.getInstance(name, surname, phoneNo, products);

        FirebaseUser user = firebaseAuth.getCurrentUser();
        databaseReference.child(user.getUid()).setValue(userinformation);
        Toast.makeText(getApplicationContext(),"User information updated",Toast.LENGTH_LONG).show();
    }

    @Override
    public void onClick(View view) {

        if (view == btnSave) {
            if (imagePath == null) {
                Drawable drawable = this.getResources().getDrawable(R.drawable.avatar);
                Bitmap bitmap = BitmapFactory.decodeResource(getResources(),R.drawable.avatar);
                // openSelectProfilePictureDialog();
                userInformation();
                // sendUserData();
                finish();
                startActivity(new Intent(EditProfileActivity.this, NavigationDrawerActivity.class));
            }
            else {
                userInformation();
                sendUserData();
                finish();
                startActivity(new Intent(EditProfileActivity.this, NavigationDrawerActivity.class));
            }
        }
    }

    private void sendUserData() {
        //User id/Images/Profile Pic.jpg
        StorageReference imageReference = storageReference.child(firebaseAuth.getUid()).child("Images").child("Profile Pic");
        UploadTask uploadTask = imageReference.putFile(imagePath);
        uploadTask.addOnFailureListener(e -> Toast.makeText(EditProfileActivity.this, "Error: Uploading profile picture", Toast.LENGTH_SHORT).show())
                .addOnSuccessListener(taskSnapshot -> Toast.makeText(EditProfileActivity.this, "Profile picture uploaded", Toast.LENGTH_SHORT).show());
    }
}
