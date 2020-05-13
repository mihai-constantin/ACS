package com.joker.bidit.dashboard;

import android.content.Intent;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.google.firebase.storage.UploadTask;
import com.joker.bidit.R;
import com.joker.bidit.addProduct.AddProductActivity;
import com.joker.bidit.navigationDrawer.ui.gallery.GalleryFragment;
import com.squareup.picasso.Picasso;

import java.util.concurrent.TimeUnit;

public class ViewProductActivity extends AppCompatActivity {

    public String price;

    // componentele din ecran
    private EditText productName;
    private ImageView productPicture;
    private EditText productColor;
    private EditText productWeight;
    private EditText productCurrentPrice;
    private TextView chronometer;
    private SeekBar seek_bar;
    private Button placeBidButton;

    private Double bidPrice;
    public static String updated_price;

    public static Integer pressBidButton;

    private static final String FORMAT = "%02d:%02d:%02d";

    boolean bidOver;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_view_product2);

        pressBidButton = 0;
        bidOver = false;

        Intent intent = getIntent();
        String name = intent.getStringExtra(GalleryFragment.NAME);
        String color = intent.getStringExtra(GalleryFragment.COLOR);
        String weight = intent.getStringExtra(GalleryFragment.WEIGHT);
        //String photo = intent.getStringExtra(GalleryFragment.PHOTO_URL);
        price = intent.getStringExtra(GalleryFragment.PRICE);


        initView();

        if (price != null) {
            productName.setText(name);
            productColor.setText(color);
            productWeight.setText(weight);
            productCurrentPrice.setText(price);

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
            Picasso.get().load(uri).fit().into(productPicture);
        });

            bidPrice = Double.parseDouble(price);
            seek_bar.setProgress(bidPrice.intValue());
        }

        seek_bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                int price = seekBar.getProgress();
                String priceEuro = price + " RON";
                productCurrentPrice.setText(priceEuro);
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
    }

    private void initView() {
        productName = findViewById(R.id.productName);
        productColor = findViewById(R.id.productColor);
        productWeight = findViewById(R.id.productWeight);
        productPicture = findViewById(R.id.productPicture);
        productCurrentPrice = findViewById(R.id.productCurrentPrice);
        placeBidButton = findViewById(R.id.placeBidButton);

        seek_bar = findViewById(R.id.seek_bar);

        seek_bar.setMax(1000);

        chronometer = findViewById(R.id.chronometer);
        new CountDownTimer(20069, 1000) { // adjust the milli seconds here

            public void onTick(long millisUntilFinished) {

                chronometer.setText("" + String.format(FORMAT,
                        TimeUnit.MILLISECONDS.toHours(millisUntilFinished),
                        TimeUnit.MILLISECONDS.toMinutes(millisUntilFinished) - TimeUnit.HOURS.toMinutes(
                                TimeUnit.MILLISECONDS.toHours(millisUntilFinished)),
                        TimeUnit.MILLISECONDS.toSeconds(millisUntilFinished) - TimeUnit.MINUTES.toSeconds(
                                TimeUnit.MILLISECONDS.toMinutes(millisUntilFinished))));
            }

            public void onFinish() {
                bidOver = true;
                seek_bar.setVisibility(View.GONE);
                placeBidButton.setVisibility(View.GONE);
                chronometer.setText("THIS PRODUCT IS NO LONGER AVAILABLE");
            }
        }.start();

        //seek_bar = findViewById(R.id.seek_bar);

        //seek_bar.setMax(1000);
    }

    public void bntOnClick(View view) {
        if (price != null) {
            // update info product
            updated_price = Integer.toString(seek_bar.getProgress());

            if (!bidOver) {
                if (Double.parseDouble(updated_price) > Double.parseDouble(price)) {
                    productCurrentPrice.setText(updated_price);
                    pressBidButton = 1;
                    Toast.makeText(this, "UPDATE PRICE",
                            Toast.LENGTH_LONG).show();
                    finish();
                } else {
                    Toast.makeText(this, "PRICE NOT UPDATED",
                            Toast.LENGTH_LONG).show();
                }

            } else {


            }



        }


    }


}
