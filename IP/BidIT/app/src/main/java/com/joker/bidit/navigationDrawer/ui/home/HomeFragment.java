package com.joker.bidit.navigationDrawer.ui.home;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.joker.bidit.R;
import com.joker.bidit.addProduct.AddProductActivity;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.dashboard.ProductAdaptor;
import com.joker.bidit.dashboard.ProductsClickListener;
import com.joker.bidit.dashboard.RecyclerTouchListener;
import com.joker.bidit.login.UserInformation;

import java.util.ArrayList;
import java.util.List;

import static java.lang.Double.parseDouble;

public class HomeFragment extends Fragment {

    public static final String NAME = "PRODUCT_NAME";
    public static final String COLOR = "PRODUCT_COLOR";
    public static final String WEIGHT = "PRODUCT_WEIGHT";
    public static final String PRICE = "PRODUCT_PRICE";

    public static Integer POSITION = -1;

    View root;

    private static List<Product> mProducts;
    private RecyclerView recyclerViewProducts;
    private ProductAdaptor adapter;

    Context context;
    public static List<Product> mFavoriteProducts = new ArrayList<>();

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        root = inflater.inflate(R.layout.activity_products, container, false);
        context = getActivity();

        if (UserInformation.getInstance() == null)
            mProducts = new ArrayList<>();
        else
            mProducts = UserInformation.getInstance().getProducts();

        populateRecyclerView();

        return root;
    }

    @Override
    public void onResume() {
        super.onResume();

        if (HomeFragment.POSITION != -1 && AddProductActivity.pressSaveButton == 1) {


            // update info product
            mProducts.get(HomeFragment.POSITION).setName(AddProductActivity.updated_name);
            mProducts.get(HomeFragment.POSITION).setColour(AddProductActivity.updated_color);
            mProducts.get(HomeFragment.POSITION).setPrice(parseDouble(AddProductActivity.updated_price));
            mProducts.get(HomeFragment.POSITION).setWeight(parseDouble(AddProductActivity.updated_weight));

            adapter.notifyDataSetChanged();

            HomeFragment.POSITION = -1;
        } else {
            if (AddProductActivity.ADD_NEW_PRODUCT == 1 && AddProductActivity.pressSaveButton == 1) {
//                Product new_product = new Product(AddProductActivity.updated_color,
//                        parseDouble(AddProductActivity.updated_weight),
//                        AddProductActivity.updated_name,
//                        parseDouble(AddProductActivity.updated_price));

//                mProducts.add(new_product);
                adapter.notifyDataSetChanged();
                AddProductActivity.ADD_NEW_PRODUCT = 0;
            }
        }
    }

    private void populateRecyclerView() {
        recyclerViewProducts = root.findViewById(R.id.recyclerViewProducts);
        // recyclerViewProducts.setHasFixedSize(true);

        recyclerViewProducts.setLayoutManager(new LinearLayoutManager(getActivity()));

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
                boolean fav = mProducts.get(position).isFavourite();

                if (!fav) {
                    mProducts.get(position).setFavourite(true);
                    ToggleButton fav_button2 = view.findViewById(R.id.button_favorite_full);
                    fav_button2.setVisibility(View.VISIBLE);

                    ToggleButton fav_button = view.findViewById(R.id.button_favorite);
                    fav_button.setVisibility(View.INVISIBLE);

                    Product product = mProducts.get(position);
                    mFavoriteProducts.add(product);
                }
                else {
                    mProducts.get(position).setFavourite(false);
                    ToggleButton fav_button2 = view.findViewById(R.id.button_favorite_full);
                    fav_button2.setVisibility(View.INVISIBLE);

                    ToggleButton fav_button = view.findViewById(R.id.button_favorite);
                    fav_button.setVisibility(View.VISIBLE);

                    Product product = mProducts.get(position);
                    mFavoriteProducts.remove(product);
                }
            }
        }));
    }

    public static List<Product> getProducts() {
        return mProducts;
    }
}