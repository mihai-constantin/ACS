package com.joker.bidit.accountInfo;

import androidx.appcompat.app.AppCompatActivity;

import android.net.Uri;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.tasks.OnSuccessListener;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;
import com.joker.bidit.MainActivity;
import com.joker.bidit.R;
import com.joker.bidit.login.UserInformation;
import com.squareup.picasso.Picasso;

public class GetInfoActivity extends AppCompatActivity {

    private TextView mTextViewUserName;
    private TextView mTextViewEmailUser;
    private ImageView mImageViewUser;

    private DatabaseReference databaseReference;
    private FirebaseAuth firebaseAuth;
    private FirebaseDatabase firebaseDatabase;
    private FirebaseStorage firebaseStorage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_get_info);

        mTextViewUserName = findViewById(R.id.textViewUserName);
        mTextViewEmailUser = findViewById(R.id.textViewEmailUser);
        mImageViewUser = findViewById(R.id.imageViewUser);

        databaseReference = FirebaseDatabase.getInstance().getReference();
        firebaseAuth = FirebaseAuth.getInstance();
        firebaseDatabase = FirebaseDatabase.getInstance();
        firebaseStorage = FirebaseStorage.getInstance();

        DatabaseReference databaseReference = firebaseDatabase.getReference(firebaseAuth.getUid());
        StorageReference storageReference = firebaseStorage.getReference();

        if(MainActivity.GOOGLE_AUTH == 1) {
            setNavigationCredentials();
        }
        else {
            // Get the image stored on Firebase via "User id/Images/Profile Pic.jpg".
            storageReference.child(firebaseAuth.getUid()).child("Images").child("Profile Pic")
                    .getDownloadUrl().addOnSuccessListener(uri -> {
                // Using "Picasso" (http://square.github.io/picasso/) after adding the dependency in the Gradle.
                // ".fit().centerInside()" fits the entire image into the specified area.
                // Finally, add "READ" and "WRITE" external storage permissions in the Manifest.
                Picasso.get().load(uri).fit().centerInside().into(mImageViewUser);
            });

            final FirebaseUser user = firebaseAuth.getCurrentUser();
            databaseReference.addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(DataSnapshot dataSnapshot) {
                    UserInformation userProfile = dataSnapshot.getValue(UserInformation.class);
                    mTextViewUserName.setText(userProfile.getUserName());
//                profileSurnameTextView.setText(userProfile.getUserSurname());
//                profilePhonenoTextView.setText(userProfile.getUserPhoneno());
                    mTextViewEmailUser.setText(user.getEmail());
                }

                @Override
                public void onCancelled(DatabaseError databaseError) {
                    Toast.makeText(GetInfoActivity.this, databaseError.getCode(),
                            Toast.LENGTH_SHORT).show();
                }
            });

        }

    }

    private void setNavigationCredentials() {

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
