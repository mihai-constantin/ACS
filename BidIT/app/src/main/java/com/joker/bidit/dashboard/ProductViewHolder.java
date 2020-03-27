package com.joker.bidit.dashboard;

import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.joker.bidit.R;

public class ProductViewHolder extends RecyclerView.ViewHolder {

    public ImageView mImageView;
    public TextView mTextViewName;
    public TextView mTextViewColorAndWeight;
    public TextView mTextViewPrice;

    public ProductViewHolder(@NonNull View itemView) {
        super(itemView);

        mImageView = itemView.findViewById(R.id.imageview_product);
        mTextViewName = itemView.findViewById(R.id.textview_name);
        mTextViewColorAndWeight = itemView.findViewById(R.id.textview_color_and_weight);
        mTextViewPrice = itemView.findViewById(R.id.textview_price);

    }


}
