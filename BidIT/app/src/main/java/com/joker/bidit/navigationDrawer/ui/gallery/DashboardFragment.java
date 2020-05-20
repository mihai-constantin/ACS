package com.joker.bidit.navigationDrawer.ui.gallery;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.firebase.auth.UserInfo;
import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.joker.bidit.R;
import com.joker.bidit.addProduct.AddProductActivity;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.dashboard.ProductAdaptor;
import com.joker.bidit.dashboard.ProductsClickListener;
import com.joker.bidit.dashboard.RecyclerTouchListener;
import com.joker.bidit.dashboard.ViewProductActivity;
import com.joker.bidit.login.UserInformation;

import java.util.ArrayList;
import java.util.List;

import static java.lang.Double.parseDouble;

public class DashboardFragment extends Fragment {

    public static final String NAME = "PRODUCT_NAME";
    public static final String COLOR = "PRODUCT_COLOR";
    public static final String WEIGHT = "PRODUCT_WEIGHT";
    public static final String PRICE = "PRODUCT_PRICE";
    public static final String PHOTO_URL = "PRODUCT_PHOTO_URL";
    public static Integer POSITION = -1;
    View root;
    private List<Product> mProducts = new ArrayList<>();
    private RecyclerView recyclerViewProducts;
    private ProductAdaptor adapter;
    Context context;

    private static final String TAG = "TAG";

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        root = inflater.inflate(R.layout.activity_dashboard, container, false);
        context = getActivity();
        populateRecyclerView();
        return root;
    }
    @Override
    public void onResume() {
        super.onResume();

        //Toast.makeText(context, "I'm back", Toast.LENGTH_LONG).show();
        if (DashboardFragment.POSITION != -1 && ViewProductActivity.pressBidButton == 1) {
            // update info product
            //mProducts.get(GalleryFragment.POSITION).setName(ViewProductActivity.updated_name);
            //mProducts.get(GalleryFragment.POSITION).setColour(ViewProductActivity.updated_color);
            mProducts.get(DashboardFragment.POSITION).setPrice(parseDouble(ViewProductActivity.updated_price));
            //mProducts.get(GalleryFragment.POSITION).setWeight(parseDouble(ViewProductActivity.updated_weight));
            adapter.notifyDataSetChanged();
            DashboardFragment.POSITION = -1;
        }
//        else {
//            if (AddProductActivity.ADD_NEW_PRODUCT == 1 && AddProductActivity.pressSaveButton == 1) {
//                // TODO - select imagine
//                Product new_product = new Product("culoare", 2.4, "name", 100.0);
//                mProducts.add(new_product);
//                adapter.notifyDataSetChanged();
//                AddProductActivity.ADD_NEW_PRODUCT = 0;
//            }
//        }
    }

    private void populateRecyclerView() {
        recyclerViewProducts = root.findViewById(R.id.recyclerViewProducts);
        // recyclerViewProducts.setHasFixedSize(true);

        recyclerViewProducts.setLayoutManager(new LinearLayoutManager(getActivity()));

        getProducts();

        adapter = new ProductAdaptor(getActivity(), mProducts);
        recyclerViewProducts.setAdapter(adapter);
        adapter.notifyDataSetChanged();
        setRecyclerViewListener();
    }

    private void setRecyclerViewListener() {
        recyclerViewProducts.addOnItemTouchListener(new RecyclerTouchListener(context,
                recyclerViewProducts, new ProductsClickListener() {
            @Override
            public void onClick(View view, final int position) {
                Product product = mProducts.get(position);
                String name = product.getName();
                String color = product.getColor();
                String weight = product.getWeight().toString();
                String price = product.getPrice().toString();
//                Toast.makeText(context, getString(R.string.single_click) + message,
//                        Toast.LENGTH_SHORT).show();
                POSITION = position;
                Intent viewProductActivity = new Intent(adapter.getContext(), ViewProductActivity.class);
                viewProductActivity.putExtra(DashboardFragment.NAME, name);
                viewProductActivity.putExtra(DashboardFragment.COLOR, color);
                viewProductActivity.putExtra(DashboardFragment.WEIGHT, weight);
                viewProductActivity.putExtra(DashboardFragment.PRICE, price);
                startActivity(viewProductActivity);
            }
            @Override
            public void onLongClick(View view, int position) {
                Toast.makeText(context, getString(R.string.long_click) + position,
                        Toast.LENGTH_LONG).show();
            }
        }));
    }

    private void getProducts() {

        mProducts = new ArrayList<>();
//        Product product1 = new Product("rosu", 3.0, "book.png", 200);
//        Product product2 = new Product("negru", 100.0, "pian.jpg", 800);
//        Product product3 = new Product("gri", 1.0, "prajitor.jpg", 100);
//        Product product4 = new Product("gri", 3.5, "Laptop", 580);
//        Product product5 = new Product("negru", 2.5, "televizor.jpg", 600);
//        mProducts.add(product1);
//        mProducts.add(product2);
//        mProducts.add(product3);
//        mProducts.add(product4);
//        mProducts.add(product5);

        GetProductsFromDB getProductsFromDB = new GetProductsFromDB();
        mProducts = getProductsFromDB.getProducts();
        Log.d(DashboardFragment.TAG, "SIZE: " + mProducts.size());
    }

}
