package com.joker.bidit.navigationDrawer;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.view.Menu;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.navigation.NavigationView;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.joker.bidit.R;
import com.joker.bidit.accountInfo.GetInfoActivity;
import com.joker.bidit.addProduct.AddProductActivity;
import com.squareup.picasso.Picasso;

import androidx.annotation.NonNull;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

public class NavigationDrawerActivity extends AppCompatActivity {

    private AppBarConfiguration mAppBarConfiguration;

    private TextView mTextViewUserName;
    private TextView mTextViewEmailUser;
    private ImageView mImageViewUser;

    private FirebaseStorage firebaseStorage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_navigation_drawer);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(NavigationDrawerActivity.this, AddProductActivity.class));
            }
        });
        DrawerLayout drawer = findViewById(R.id.drawer_layout);
        NavigationView navigationView = findViewById(R.id.nav_view);
        // Passing each menu ID as a set of Ids because each
        // menu should be considered as top level destinations.
        mAppBarConfiguration = new AppBarConfiguration.Builder(
                R.id.nav_home, R.id.nav_gallery, R.id.nav_slideshow)
                .setDrawerLayout(drawer)
                .build();

        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        NavigationUI.setupActionBarWithNavController(this, navController, mAppBarConfiguration);
        NavigationUI.setupWithNavController(navigationView, navController);

        setNavigationCredentials();
    }

    private void setNavigationCredentials() {
        NavigationView navigationView = findViewById(R.id.nav_view);
        View headerView = navigationView.getHeaderView(0);
        mTextViewUserName = headerView.findViewById(R.id.textViewUserName);
        mTextViewEmailUser = headerView.findViewById(R.id.textViewEmailUser);
        mImageViewUser = headerView.findViewById(R.id.imageViewUser);

        GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(this);
        if(account != null) {
            String username = account.getDisplayName();
            String email = account.getEmail();
            String photo = account.getPhotoUrl().toString();

            mTextViewUserName.setText(username);
            mTextViewEmailUser.setText(email);

            Picasso.get()
                    .load(photo)
                    .resize(300,300)
                    .centerCrop()
                    .into(mImageViewUser);
        }
        else {
            FirebaseAuth mAuth = FirebaseAuth.getInstance();
            FirebaseUser user = mAuth.getCurrentUser();

            assert user != null;
            mTextViewEmailUser.setText(user.getEmail());

//            Picasso.get()
//                    .load("https://www.freepngimg.com/thumb/google/66726-customer-account-google-service-button-search-logo.png")
//                    .resize(300,300)
//                    .centerCrop()
//                    .into(mImageViewUser);

            firebaseStorage = FirebaseStorage.getInstance();
            StorageReference storageReference = firebaseStorage.getReference();
            // Get the image stored on Firebase via "User id/Images/Profile Pic.jpg".
            storageReference.child(mAuth.getUid()).child("Images").child("Profile Pic").getDownloadUrl().addOnSuccessListener(uri -> {
                // Using "Picasso" (http://square.github.io/picasso/) after adding the dependency in the Gradle.
                // ".fit().centerInside()" fits the entire image into the specified area.
                // Finally, add "READ" and "WRITE" external storage permissions in the Manifest.
                Picasso.get().load(uri).fit().centerInside().into(mImageViewUser);
            });
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.navigation_drawer, menu);
        return true;
    }

    @Override
    public boolean onSupportNavigateUp() {
        NavController navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        return NavigationUI.navigateUp(navController, mAppBarConfiguration)
                || super.onSupportNavigateUp();
    }

    public void signOut(MenuItem item) {
        FirebaseAuth mAuth = FirebaseAuth.getInstance();
        GoogleSignInOptions gso;
        GoogleSignInClient mGoogleSignInClient;

        Toast.makeText(NavigationDrawerActivity.this,
                String.format("Goodbye, %s", FirebaseAuth.getInstance().getCurrentUser().getEmail()),
                Toast.LENGTH_SHORT).show();

        mAuth.signOut();

        gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestIdToken(getString(R.string.default_web_client_id))
                .requestEmail()
                .build();

        // Build a GoogleSignInClient with the options specified by gso.
        mGoogleSignInClient = GoogleSignIn.getClient(this, gso);

        mGoogleSignInClient.revokeAccess().addOnCompleteListener(this,
                task -> {
                    // updateUI(null);
                });

        finish();
    }

    public void getUserInfo(View view) {
        startActivity(new Intent(NavigationDrawerActivity.this, GetInfoActivity.class));
    }
}
