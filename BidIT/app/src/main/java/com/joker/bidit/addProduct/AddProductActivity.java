package com.joker.bidit.addProduct;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;

import com.joker.bidit.R;
import com.joker.bidit.navigationDrawer.ui.home.HomeFragment;
import com.squareup.picasso.Picasso;

public class AddProductActivity extends AppCompatActivity {

    private EditText productNameEditText;
    private EditText productColorEditText;
    private EditText productWeightEditText;
    private ImageView cover_image;
    private TextView price_ron;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_product);

        initView();

        Intent intent = getIntent();
        String name = intent.getStringExtra(HomeFragment.NAME);
        String color = intent.getStringExtra(HomeFragment.COLOR);
        String weight = intent.getStringExtra(HomeFragment.WEIGHT);
        String photo = intent.getStringExtra(HomeFragment.PHOTO_URL);
        String price = intent.getStringExtra(HomeFragment.PRICE);

        productNameEditText.setText(name);
        productColorEditText.setText(color);
        productWeightEditText.setText(weight);

        Picasso.get().load(photo)
                .into(cover_image);

        price_ron.setText(price + " RON");
    }

    private void initView() {
        productNameEditText = findViewById(R.id.productNameEditText);
        productColorEditText = findViewById(R.id.productColorEditText);
        productWeightEditText = findViewById(R.id.productWeightEditText);
        cover_image = findViewById(R.id.cover_image);
        price_ron = findViewById(R.id.price_ron);
    }

    public void btnTakePictureFromGalleryOnClick(View view) {
    }

    public void bntTakePictureFromCameraOnClick(View view) {
    }

    public void bntOnClick(View view) {
        finish();
    }
}
