package com.joker.bidit.navigationDrawer.ui.home;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.joker.bidit.R;
import com.joker.bidit.dashboard.Product;
import com.joker.bidit.dashboard.ProductAdaptor;

import java.util.ArrayList;
import java.util.List;

public class HomeFragment extends Fragment {

    View root;

    private List<Product> mProducts;
    private RecyclerView recyclerViewProducts;
    private ProductAdaptor adapter;

    Context context;

    public View onCreateView(@NonNull LayoutInflater inflater,
                             ViewGroup container, Bundle savedInstanceState) {

        root = inflater.inflate(R.layout.activity_products, container, false);
        context = getActivity();
        populateRecyclerView();

        return root;
    }

    private void populateRecyclerView() {
       recyclerViewProducts = root.findViewById(R.id.recyclerViewProducts);
       recyclerViewProducts.setHasFixedSize(true);

       recyclerViewProducts.setLayoutManager(new LinearLayoutManager(getActivity()));

       getProducts();

       adapter = new ProductAdaptor(getActivity(), mProducts);
       recyclerViewProducts.setAdapter(adapter);
       adapter.notifyDataSetChanged();
    }

    private void getProducts() {
        mProducts = new ArrayList<>();
        Product product1 = new Product("red", 3.0, "Book", 200,
                "https://images.unsplash.com/photo-1510546462255-979b0e0ca1b5?w=800&q=60");
        Product product2 = new Product("pink", 2.0, "Scarf", 20,
                "https://images.unsplash.com/photo-1514207994142-98522b5a2b23?w=800&q=60");
        Product product3 = new Product("blue", 5.0, "T-shirt", 160,
                "https://images.unsplash.com/photo-1512909481869-0eaa1e9817ba?w=800&q=60");
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
        mProducts.add(product2);
        mProducts.add(product3);
//        mProducts.add(product4);
//        mProducts.add(product5);
//        mProducts.add(product6);
//        mProducts.add(product7);
//        mProducts.add(product8);
//        mProducts.add(product9);
//        mProducts.add(product10);
    }
}
