package com.joker.bidit.dashboard;

import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.joker.bidit.R;
import com.squareup.picasso.Picasso;

import java.util.List;

public class ProductAdapter extends RecyclerView.Adapter<ProductViewHolder> {

    private List<Product> mProducts;

    public ProductAdapter(List<Product> mProducts) {
        this.mProducts = mProducts;
    }

    @NonNull
    @Override
    public ProductViewHolder onCreateViewHolder(@NonNull ViewGroup viewGroup, int i) {
        View productView = LayoutInflater.from(viewGroup.getContext()).
                inflate(R.layout.product_item, viewGroup, false);

        return new ProductViewHolder(productView);
    }

    @Override
    public void onBindViewHolder(@NonNull ProductViewHolder productViewHolder, int i) {
        Product product = mProducts.get(i);

        productViewHolder.mTextViewName.setText(product.getName());
        productViewHolder.mTextViewColorAndWeight.setText(product.getColor() + " /" +
                product.getWeight());
        productViewHolder.mTextViewPrice.setText(product.getPrice() + " RON");

        Picasso.get().load(product.getPicture())
                .into(productViewHolder.mImageView);
    }

    @Override
    public int getItemCount() {
        return mProducts.size();
    }
}
