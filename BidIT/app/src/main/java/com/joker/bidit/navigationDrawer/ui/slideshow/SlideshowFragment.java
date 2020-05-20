package com.joker.bidit.navigationDrawer.ui.slideshow;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProviders;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.joker.bidit.R;
import com.joker.bidit.addProduct.AddProductActivity;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.dashboard.ProductAdaptor;
import com.joker.bidit.dashboard.ProductsClickListener;
import com.joker.bidit.dashboard.RecyclerTouchListener;
import com.joker.bidit.login.UserInformation;
import com.joker.bidit.navigationDrawer.ui.home.HomeFragment;

import java.util.ArrayList;

public class SlideshowFragment extends Fragment {

    View root;
    Context context;

    public static Integer POSITION = -1;

    private RecyclerView recyclerViewProducts;
    private ProductAdaptor adapter;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        root = inflater.inflate(R.layout.activity_products, container, false);
        context = getActivity();

        populateRecyclerView();

        return root;
    }

    private void populateRecyclerView() {
        recyclerViewProducts = root.findViewById(R.id.recyclerViewProducts);
        // recyclerViewProducts.setHasFixedSize(true);

        recyclerViewProducts.setLayoutManager(new LinearLayoutManager(getActivity()));

        adapter = new ProductAdaptor(getActivity(), HomeFragment.mFavoriteProducts);
        recyclerViewProducts.setAdapter(adapter);
        adapter.notifyDataSetChanged();

        setRecyclerViewListener();
    }

    private void setRecyclerViewListener() {
        recyclerViewProducts.addOnItemTouchListener(new RecyclerTouchListener(context,
                recyclerViewProducts, new ProductsClickListener() {
            @Override
            public void onClick(View view, final int position) {

                Product product = HomeFragment.mFavoriteProducts.get(position);
                String name = product.getName();
                String color = product.getColor();
                String weight = product.getWeight().toString();
                String price = product.getPrice().toString();

                Toast.makeText(context, getString(R.string.single_click) + " " + position,
                        Toast.LENGTH_SHORT).show();

                POSITION = position;

                Intent secondActivity = new Intent(adapter.getContext(), AddProductActivity.class);
                secondActivity.putExtra(HomeFragment.NAME, name);
                secondActivity.putExtra(HomeFragment.COLOR, color);
                secondActivity.putExtra(HomeFragment.WEIGHT, weight);
                secondActivity.putExtra(HomeFragment.PRICE, price);
                startActivity(secondActivity);
            }

            @Override
            public void onLongClick(View view, int position) {
                Toast.makeText(context, getString(R.string.long_click) + position,
                        Toast.LENGTH_LONG).show();

                HomeFragment.mFavoriteProducts.remove(position);
                adapter.notifyDataSetChanged();
            }
        }));
    }
}
