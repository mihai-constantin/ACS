package com.joker.bidit.addProduct;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.SeekBar;
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
    private SeekBar seek_bar;

    public static String updated_name;
    public static String updated_color;
    public static String updated_weight;
    public static String updated_price;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_product);

        Intent intent = getIntent();
        String name = intent.getStringExtra(HomeFragment.NAME);
        String color = intent.getStringExtra(HomeFragment.COLOR);
        String weight = intent.getStringExtra(HomeFragment.WEIGHT);
        String photo = intent.getStringExtra(HomeFragment.PHOTO_URL);
        String price = intent.getStringExtra(HomeFragment.PRICE);

        initView();

        if (price != null) {
            productNameEditText.setText(name);
            productColorEditText.setText(color);
            productWeightEditText.setText(weight);

            Picasso.get().load(photo)
                    .into(cover_image);

            price_ron.setText(price + " RON");

            Double initialPrice = Double.parseDouble(price);
            seek_bar.setProgress(initialPrice.intValue());

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
    }

    public void bntTakePictureFromCameraOnClick(View view) {
    }

    public void bntOnClick(View view) {
        if (productNameEditText != null) {
            updated_name = productNameEditText.getText().toString();
            updated_color = productColorEditText.getText().toString();
            updated_weight = productWeightEditText.getText().toString();
            updated_price = Integer.toString(seek_bar.getProgress());
        }

        finish();
    }
}
