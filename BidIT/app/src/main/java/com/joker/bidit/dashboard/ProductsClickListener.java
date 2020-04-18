package com.joker.bidit.dashboard;

import android.view.View;

public interface ProductsClickListener {

    void onClick(View view, int position);

    void onLongClick(View view, int position);
}
