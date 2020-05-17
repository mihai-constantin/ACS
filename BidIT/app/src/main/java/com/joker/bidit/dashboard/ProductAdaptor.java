package com.joker.bidit.dashboard;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.joker.bidit.R;
import com.squareup.picasso.Picasso;

import java.util.List;

public class ProductAdaptor extends RecyclerView.Adapter<ProductsViewHolder> {

    private List<Product> products;
    private Context context;


    public Context getContext() {
        return context;
    }

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
                .inflate(R.layout.destination_item, parent, false);
        return new ProductsViewHolder(itemView);
    }

    @Override
    public void onBindViewHolder(@NonNull ProductsViewHolder holder, int position) {
        Product currentProduct = products.get(position);

        holder.mTextViewName.setText(currentProduct.getName());
        holder.mTextViewColorAndWeight.setText(currentProduct.getColor() + " /" +currentProduct.getWeight());
        holder.mTextViewPrice.setText(currentProduct.getPrice() + " RON");

        // TODO - get image from db by name
        FirebaseAuth firebaseAuth = FirebaseAuth.getInstance();
        FirebaseStorage firebaseStorage = FirebaseStorage.getInstance();
        StorageReference storageReference = firebaseStorage.getReference();
        // Get the image stored on Firebase via "User id/Products/name_product.jpg".

        Toast.makeText(context, "Searching for " + currentProduct.getName(),
                Toast.LENGTH_LONG).show();

        storageReference.child(firebaseAuth.getUid()).child("Products").child(currentProduct.getName())
                .getDownloadUrl().addOnSuccessListener(uri -> {
            // Using "Picasso" (http://square.github.io/picasso/) after adding the dependency in the Gradle.
            // ".fit().centerInside()" fits the entire image into the specified area.
            // Finally, add "READ" and "WRITE" external storage permissions in the Manifest.
            Picasso.get().load(uri).fit().into(holder.getImageView());
        });

    }

    @Override
    public int getItemCount() {
        return products.size();
    }
}
