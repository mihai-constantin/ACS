package com.joker.bidit.dashboard;

import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.joker.bidit.R;

public class ProductsViewHolder extends RecyclerView.ViewHolder {

    public ImageView mImageView;
    public TextView mTextViewName;
    public TextView mTextViewColorAndWeight;
    public TextView mTextViewPrice;

    public ProductsViewHolder(@NonNull View itemView) {
        super(itemView);

        mImageView = itemView.findViewById(R.id.imageview_product);
        mTextViewName = itemView.findViewById(R.id.textview_name);
        mTextViewColorAndWeight = itemView.findViewById(R.id.textview_color_and_weight);
        mTextViewPrice = itemView.findViewById(R.id.textview_price);
    }

    public ImageView getImageView() {
        return mImageView;
    }

    public TextView getTextViewName() {
        return mTextViewName;
    }

    public TextView getTextViewColorAndWeight() {
        return mTextViewColorAndWeight;
    }

    public TextView getTextViewPrice() {
        return mTextViewPrice;
    }
}
