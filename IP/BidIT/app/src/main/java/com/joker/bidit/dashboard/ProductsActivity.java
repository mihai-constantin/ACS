package com.joker.bidit.dashboard;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.joker.bidit.R;
import com.joker.bidit.login.UserInformation;

import java.util.ArrayList;
import java.util.List;

public class ProductsActivity extends AppCompatActivity {

    private List<Product> mProducts;
    private RecyclerView recyclerViewProducts;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_products);

        initView();
        getProducts();
        setLayoutManager();
        setAdapter();
        setRecyclerViewListener();
    }

    private void setRecyclerViewListener() {
        recyclerViewProducts.addOnItemTouchListener(new RecyclerTouchListener(this,
                recyclerViewProducts, new ProductsClickListener() {
            @Override
            public void onClick(View view, final int position) {
                Toast.makeText(ProductsActivity.this, getString(R.string.single_click) + position,
                        Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onLongClick(View view, int position) {
                Toast.makeText(ProductsActivity.this, getString(R.string.long_click) + position,
                        Toast.LENGTH_LONG).show();
            }
        }));
    }

    private void initView() {
        recyclerViewProducts = findViewById(R.id.recyclerViewProducts);
    }

    private void setLayoutManager() {
        RecyclerView.LayoutManager layoutManager = new LinearLayoutManager(this);
        recyclerViewProducts.setLayoutManager(layoutManager);
    }

    private void setAdapter() {
        ProductAdaptor fruitsAdapter = new ProductAdaptor(mProducts);
        recyclerViewProducts.setAdapter(fruitsAdapter);
    }

    private void getProducts() {
       mProducts = new ArrayList<>();
    }
}
