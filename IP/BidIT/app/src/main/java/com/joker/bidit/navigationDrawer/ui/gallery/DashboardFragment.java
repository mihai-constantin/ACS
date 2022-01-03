package com.joker.bidit.navigationDrawer.ui.gallery;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.joker.bidit.R;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.dashboard.ProductAdaptor;
import com.joker.bidit.dashboard.ProductsClickListener;
import com.joker.bidit.dashboard.RecyclerTouchListener;
import com.joker.bidit.dashboard.ViewProductActivity;
import com.joker.bidit.navigationDrawer.ui.home.HomeFragment;

import java.util.ArrayList;
import java.util.List;

import static java.lang.Double.parseDouble;

public class DashboardFragment extends Fragment {

    public static final String NAME = "PRODUCT_NAME";
    public static final String COLOR = "PRODUCT_COLOR";
    public static final String WEIGHT = "PRODUCT_WEIGHT";
    public static final String PRICE = "PRODUCT_PRICE";
    public static Integer POSITION = -1;
    View root;

    public static List<Product> productsDashboard = new ArrayList<>();

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

        if (DashboardFragment.POSITION != -1 && ViewProductActivity.pressBidButton == 1) {
            // update info product
            //mProducts.get(GalleryFragment.POSITION).setName(ViewProductActivity.updated_name);
            //mProducts.get(GalleryFragment.POSITION).setColour(ViewProductActivity.updated_color);
            DashboardFragment.productsDashboard.get(DashboardFragment.POSITION)
                    .setPrice(parseDouble(ViewProductActivity.updated_price));
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

        recyclerViewProducts.setLayoutManager(new LinearLayoutManager(getActivity()));

        getProducts();

        adapter = new ProductAdaptor(getActivity(), DashboardFragment.productsDashboard);
        recyclerViewProducts.setAdapter(adapter);
        adapter.notifyDataSetChanged();
        setRecyclerViewListener();
    }

    private void setRecyclerViewListener() {
        recyclerViewProducts.addOnItemTouchListener(new RecyclerTouchListener(context,
                recyclerViewProducts, new ProductsClickListener() {
            @Override
            public void onClick(View view, final int position) {
                Product product = DashboardFragment.productsDashboard.get(position);
                String name = product.getName();
                String color = product.getColor();
                String weight = product.getWeight().toString();
                String price = product.getPrice().toString();

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

                boolean fav = DashboardFragment.productsDashboard.get(position).isFavourite();

                if (!fav) {
                    DashboardFragment.productsDashboard.get(position).setFavourite(true);
                    ToggleButton fav_button2 = view.findViewById(R.id.button_favorite_full);
                    fav_button2.setVisibility(View.VISIBLE);

                    ToggleButton fav_button = view.findViewById(R.id.button_favorite);
                    fav_button.setVisibility(View.INVISIBLE);

                    Product product = DashboardFragment.productsDashboard.get(position);
                    HomeFragment.mFavoriteProducts.add(product);
                }
                else {
                    DashboardFragment.productsDashboard.get(position).setFavourite(false);
                    ToggleButton fav_button2 = view.findViewById(R.id.button_favorite_full);
                    fav_button2.setVisibility(View.INVISIBLE);

                    ToggleButton fav_button = view.findViewById(R.id.button_favorite);
                    fav_button.setVisibility(View.VISIBLE);

                    Product product = DashboardFragment.productsDashboard.get(position);
                    HomeFragment.mFavoriteProducts.remove(product);
                }
            }
        }));
    }

    void getProducts()
    {
        productsDashboard = new ArrayList<>();
        DashboardFragment.productsDashboard.add(new Product("negru", 2.0, "chitara", 500.0, false));
        DashboardFragment.productsDashboard.add(new Product("negru", 2.0, "televizor", 250.0, false));
        DashboardFragment.productsDashboard.add(new Product("alba", 2.0, "carte", 135.0, false));
        DashboardFragment.productsDashboard.add(new Product("maro", 2.0, "ceas", 750.0, false));
        DashboardFragment.productsDashboard.add(new Product("gri", 4.0, "laptop", 800.0, false));
        DashboardFragment.productsDashboard.add(new Product("gri", 5.0, "prajitor", 120.0, false));
        DashboardFragment.productsDashboard.add(new Product("negru", 100.0, "pian", 990.0, false));

        if (HomeFragment.getProducts() != null) {
            DashboardFragment.productsDashboard.addAll(HomeFragment.getProducts());
        }
    }
}
