package com.joker.bidit.dashboard;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.joker.bidit.R;
import com.squareup.picasso.Picasso;

import java.util.List;

public class ProductAdaptor extends RecyclerView.Adapter<ProductsViewHolder> {

    private List<Product> products;
    private Context context;

    public ProductAdaptor(List<Product> products) {
        this.products = products;
    }

    public ProductAdaptor(Context context, List<Product> data) {
        this.context = context;
        this.products = data;
    }

    @NonNull
    @Override
    public ProductsViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View itemView = LayoutInflater.from(parent.getContext())
                .inflate(R.layout.product_item, parent, false);
        return new ProductsViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull ProductsViewHolder holder, int position) {
        Product currentProduct = products.get(position);

        holder.mTextViewName.setText(currentProduct.getName());
        holder.mTextViewColorAndWeight.setText(currentProduct.getColor() + " /" +
                currentProduct.getWeight());
        holder.mTextViewPrice.setText(currentProduct.getPrice() + " RON");

        Picasso.get().load(currentProduct.getPicture())
                .into(holder.getImageView());
    }

    @Override
    public int getItemCount() {
        return products.size();
    }
}
