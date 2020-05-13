package com.joker.bidit.addProduct;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SeekBar;
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
import com.joker.bidit.login.EditProfileActivity;
import com.joker.bidit.login.UserInformation;
import com.joker.bidit.navigationDrawer.ui.home.HomeFragment;
import com.squareup.picasso.Picasso;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class AddProductActivity extends AppCompatActivity {

    private EditText productNameEditText;
    private EditText productColorEditText;
    private EditText productWeightEditText;
    private ImageView cover_image;
    private TextView price_ron;
    private SeekBar seek_bar;

    public static String updated_name;
    public static String updated_color;
    public static String updated_weight;
    public static String updated_price;

    public static Integer ADD_NEW_PRODUCT = 0;

    public String price;
    public static Integer pressSaveButton;

    private static int PICK_IMAGE = 123;
    Uri imagePath;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_product);

        pressSaveButton = 0;
        ADD_NEW_PRODUCT = 0;

        Intent intent = getIntent();
        String name = intent.getStringExtra(HomeFragment.NAME);
        String color = intent.getStringExtra(HomeFragment.COLOR);
        String weight = intent.getStringExtra(HomeFragment.WEIGHT);
        price = intent.getStringExtra(HomeFragment.PRICE);

        initView();

        if (price != null) {
            productNameEditText.setText(name);
            productColorEditText.setText(color);
            productWeightEditText.setText(weight);

            // TODO - search image and load into activity
            FirebaseAuth firebaseAuth = FirebaseAuth.getInstance();
            FirebaseStorage firebaseStorage = FirebaseStorage.getInstance();
            StorageReference storageReference = firebaseStorage.getReference();
            // Get the image stored on Firebase via "User id/Products/name_product.jpg".

            storageReference.child(firebaseAuth.getUid()).child("Products").child(name)
                    .getDownloadUrl().addOnSuccessListener(uri -> {
                // Using "Picasso" (http://square.github.io/picasso/) after adding the dependency in the Gradle.
                // ".fit().centerInside()" fits the entire image into the specified area.
                // Finally, add "READ" and "WRITE" external storage permissions in the Manifest.
                Picasso.get().load(uri).fit().into(cover_image);
            });

            price_ron.setText(price + " RON");

            Double initialPrice = Double.parseDouble(price);
            seek_bar.setProgress(initialPrice.intValue());
        }

        seek_bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                int price = seekBar.getProgress();
                String priceEuro = price + " RON";
                price_ron.setText(priceEuro);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        ADD_NEW_PRODUCT = 0;
    }

    private void initView() {
        productNameEditText = findViewById(R.id.productNameEditText);
        productColorEditText = findViewById(R.id.productColorEditText);
        productWeightEditText = findViewById(R.id.productWeightEditText);
        cover_image = findViewById(R.id.cover_image);
        price_ron = findViewById(R.id.price_ron);
        seek_bar = findViewById(R.id.seek_bar);

        seek_bar.setMax(1000);
    }

    public void btnTakePictureFromGalleryOnClick(View view) {
        Intent profileIntent = new Intent();
        profileIntent.setType("image/*");
        profileIntent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(Intent.createChooser(profileIntent, "Select Image."), PICK_IMAGE);
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == PICK_IMAGE && resultCode == RESULT_OK && data.getData() != null) {
            imagePath = data.getData();
            try {
                Bitmap bitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), imagePath);
                cover_image.setImageBitmap(bitmap);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    public void bntTakePictureFromCameraOnClick(View view) {

        // TODO
    }

    public void bntOnClick(View view) {
        pressSaveButton = 1;
        if (price != null) {
            // update info product
            updated_name = productNameEditText.getText().toString();
            updated_color = productColorEditText.getText().toString();
            updated_weight = productWeightEditText.getText().toString();
            updated_price = Integer.toString(seek_bar.getProgress());

            ADD_NEW_PRODUCT = 0;
        }
        else {
            // add new product
            updated_name = productNameEditText.getText().toString();
            updated_color = productColorEditText.getText().toString();
            updated_weight = productWeightEditText.getText().toString();
            updated_price = Integer.toString(seek_bar.getProgress());

            FirebaseAuth firebaseAuth = FirebaseAuth.getInstance();
            FirebaseStorage firebaseStorage = FirebaseStorage.getInstance();
            StorageReference storageReference = firebaseStorage.getReference();

            // User id/Products/updated_name.jpg upload pic in db
            StorageReference imageReference = storageReference.child(firebaseAuth.getUid()).child("Products").child(updated_name);
            UploadTask uploadTask = imageReference.putFile(imagePath);
            uploadTask.addOnFailureListener(
                    e -> Toast.makeText(AddProductActivity.this, "Error: Uploading product picture", Toast.LENGTH_SHORT).show())
                    .addOnSuccessListener
                            (taskSnapshot -> Toast.makeText(AddProductActivity.this, "Product picture uploaded", Toast.LENGTH_SHORT).show());

            ADD_NEW_PRODUCT = 1;

            // TODO - update user info
            UserInformation userInformation = UserInformation.getInstance();
            List<Product> products = userInformation.getProducts();

            products.add(new Product(updated_color, Double.parseDouble(updated_weight), updated_name,
                    Double.parseDouble(updated_price)));

            FirebaseUser user = firebaseAuth.getCurrentUser();
            FirebaseDatabase.getInstance().getReference().child(user.getUid()).setValue(userInformation);
            Toast.makeText(getApplicationContext(),"User information updated",Toast.LENGTH_LONG).show();

            // TODO - ASTA E O MIZERIE
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }

        finish();
    }
}
