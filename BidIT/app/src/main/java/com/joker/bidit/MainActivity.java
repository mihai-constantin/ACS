package com.joker.bidit;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.joker.bidit.dashboard.RecyclerViewerActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    // display dashboard
    public void btnRecyclerViewOnClick(View view) {
        startActivity(new Intent(MainActivity.this, RecyclerViewerActivity.class));
    }
}
