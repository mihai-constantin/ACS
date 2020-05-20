package com.joker.bidit.navigationDrawer.ui.gallery;

import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.login.UserInformation;

import java.util.ArrayList;
import java.util.List;

public class GetProductsFromDB {

    List<Product> mProducts = new ArrayList<>();

    private static final String LOG_TAG = "LOG_TAG";

    public List<Product> getProducts() {
        FirebaseDatabase firebaseDatabase = FirebaseDatabase.getInstance();
        DatabaseReference ref = firebaseDatabase.getReference();

        ref.addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {

                Log.d(GetProductsFromDB.LOG_TAG, "aiciiii: " + dataSnapshot.getKey() + "; " + dataSnapshot.getValue());

                UserInformation userInformation = dataSnapshot.getValue(UserInformation.class);
                if(userInformation.getProducts() != null) {
                    mProducts.addAll(userInformation.getProducts());
                }

                Log.d(GetProductsFromDB.LOG_TAG, "products: " + mProducts);
            }

            @Override
            public void onChildChanged(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {

            }

            @Override
            public void onChildRemoved(@NonNull DataSnapshot dataSnapshot) {

            }

            @Override
            public void onChildMoved(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        return mProducts;
    }
}
