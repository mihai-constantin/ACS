package com.joker.bidit.accountInfo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.material.navigation.NavigationView;
import com.joker.bidit.R;
import com.squareup.picasso.Picasso;

public class getInfoActivity extends AppCompatActivity {

    private TextView mTextViewUserName;
    private TextView mTextViewEmailUser;
    private ImageView mImageViewUser;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_get_info);

        setNavigationCredentials();
    }

    private void setNavigationCredentials() {
        mTextViewUserName = findViewById(R.id.textViewUserName);
        mTextViewEmailUser = findViewById(R.id.textViewEmailUser);
        mImageViewUser = findViewById(R.id.imageViewUser);

        GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(this);
        if (account != null) {
            String username = account.getDisplayName();
            String email = account.getEmail();
            String photo = account.getPhotoUrl().toString();

            mTextViewUserName.setText(username);
            mTextViewEmailUser.setText(email);

            Picasso.get()
                    .load(photo)
                    .resize(300, 300)
                    .centerCrop()
                    .into(mImageViewUser);
        }

    }
}
