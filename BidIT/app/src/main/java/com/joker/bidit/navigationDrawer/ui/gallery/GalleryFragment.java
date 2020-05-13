package com.joker.bidit.navigationDrawer.ui.gallery;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

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
import com.joker.bidit.dashboard.ViewProductActivity;

import java.util.ArrayList;
import java.util.List;

import static java.lang.Double.parseDouble;

public class GalleryFragment extends Fragment {

    public static final String NAME = "PRODUCT_NAME";
    public static final String COLOR = "PRODUCT_COLOR";
    public static final String WEIGHT = "PRODUCT_WEIGHT";
    public static final String PRICE = "PRODUCT_PRICE";
    public static final String PHOTO_URL = "PRODUCT_PHOTO_URL";
    public static Integer POSITION = -1;
    View root;
    private List<Product> mProducts;
    private RecyclerView recyclerViewProducts;
    private ProductAdaptor adapter;
    Context context;
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
        if (GalleryFragment.POSITION != -1 && ViewProductActivity.pressBidButton == 1) {
            // update info product
            //mProducts.get(GalleryFragment.POSITION).setName(ViewProductActivity.updated_name);
            //mProducts.get(GalleryFragment.POSITION).setColour(ViewProductActivity.updated_color);
            mProducts.get(GalleryFragment.POSITION).setPrice(parseDouble(ViewProductActivity.updated_price));
            //mProducts.get(GalleryFragment.POSITION).setWeight(parseDouble(ViewProductActivity.updated_weight));
            adapter.notifyDataSetChanged();
            GalleryFragment.POSITION = -1;
        }
//        else {
//            if (AddProductActivity.ADD_NEW_PRODUCT == 1 && AddProductActivity.pressSaveButton == 1) {
//                // TODO - select imagine
//                Product new_product = new Product(AddProductActivity.updated_color,
//                        parseDouble(AddProductActivity.updated_weight),
//                        AddProductActivity.updated_name,
//                        parseDouble(AddProductActivity.updated_price),
//                        "https://images.unsplash.com/photo-1514192631-251f5f0b14f2?w=800&q=60");
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
                String photo = product.getPicture();
                String price = product.getPrice().toString();
//                Toast.makeText(context, getString(R.string.single_click) + message,
//                        Toast.LENGTH_SHORT).show();
                POSITION = position;
                Intent viewProductActivity = new Intent(adapter.getContext(), ViewProductActivity.class);
                viewProductActivity.putExtra(GalleryFragment.NAME, name);
                viewProductActivity.putExtra(GalleryFragment.COLOR, color);
                viewProductActivity.putExtra(GalleryFragment.WEIGHT, weight);
                viewProductActivity.putExtra(GalleryFragment.PHOTO_URL, photo);
                viewProductActivity.putExtra(GalleryFragment.PRICE, price);
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
        Product product1 = new Product("red", 3.0, "book.png", 200,
                "https://images.unsplash.com/photo-1510546462255-979b0e0ca1b5?w=800&q=60");
//        Product product2 = new Product("pink", 2.0, "Scarf", 20,
//                "https://images.unsplash.com/photo-1514207994142-98522b5a2b23?w=800&q=60");
//        Product product3 = new Product("blue", 5.0, "T-shirt", 160,
//                "https://images.unsplash.com/photo-1512909481869-0eaa1e9817ba?w=800&q=60");
//        Product product4 = new Product("white", 1.0, "Scarf", 80,
//                "https://images.unsplash.com/photo-1514192631-251f5f0b14f2?w=800&q=60");
//        Product product5 = new Product("green", 2.0, "Book", 250,
//                "https://images.unsplash.com/photo-1519894520384-1ee1adbe7bd8?w=800&q=60");
//        Product product6 = new Product("yellow", 1.5, "Toy car", 400,
//                "https://images.unsplash.com/photo-1511837008003-71eca36ceb70?w=800&q=60");
//        Product product7 = new Product("blue", 1.5, "Chocolate", 560,
//                "https://images.unsplash.com/photo-1481391319762-47dff72954d9?w=800&q=60");
//        Product product8 = new Product("magenta", 1.5, "Phone", 530,
//                "https://images.unsplash.com/photo-1480717846107-87837abec1e9?w=800&q=60");
//        Product product9 = new Product("black", 3.5, "Blazer", 520,
//                "https://images.unsplash.com/photo-1513796430146-c91cf8e4d65c?w=800&q=60");
//        Product product10 = new Product("orange", 7.0, "Shoes", 720,
//                "https://images.unsplash.com/photo-1480632563560-30f503c09195?w=800&q=60");
        mProducts.add(product1);
        //mProducts.add(product2);
        //mProducts.add(product3);
//        mProducts.add(product4);
//        mProducts.add(product5);
//        mProducts.add(product6);
//        mProducts.add(product7);
//        mProducts.add(product8);
//        mProducts.add(product9);
//        mProducts.add(product10);
    }
}
