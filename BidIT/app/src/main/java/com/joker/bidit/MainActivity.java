package com.joker.bidit;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.auth.api.signin.GoogleSignIn;
import com.google.android.gms.auth.api.signin.GoogleSignInAccount;
import com.google.android.gms.auth.api.signin.GoogleSignInClient;
import com.google.android.gms.auth.api.signin.GoogleSignInOptions;
import com.google.android.gms.common.SignInButton;
import com.google.android.gms.common.api.ApiException;
import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthCredential;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.auth.GoogleAuthProvider;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.joker.bidit.login.Authentication;
import com.joker.bidit.login.EditProfileActivity;
import com.joker.bidit.login.ResetPasswordActivity;
import com.joker.bidit.login.UserInformation;
import com.joker.bidit.navigationDrawer.NavigationDrawerActivity;
import com.joker.bidit.utils.EmailHelper;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText mEditTextEmail;
    private EditText mEditTextPhone;
    private CheckBox mCheckBoxAccept;
    private Button mLogginButton;
    private TextView mForgotPasswordButton;

    private Authentication mAuthentication;
    private GoogleSignInClient mGoogleSignInClient;
    private FirebaseAuth mAuth;

    private static final int RC_SIGN_IN = 9001;
    private static final String TAG = "SignInActivity";
    private GoogleSignInOptions gso;
    public static int GOOGLE_AUTH = 0;
    private int times = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        GOOGLE_AUTH = 0;

        mAuthentication = new Authentication();
        initView();

        setGooglePlusButtonText(findViewById(R.id.sign_in_button),
                getString(R.string.continueWithGoogle));

        mAuth = FirebaseAuth.getInstance();

        // Configure sign-in to request the user's ID, email address, and basic
        // profile. ID and basic profile are included in DEFAULT_SIGN_IN.
        gso = new GoogleSignInOptions.Builder(GoogleSignInOptions.DEFAULT_SIGN_IN)
                .requestIdToken(getString(R.string.default_web_client_id))
                .requestEmail()
                .build();

        // Build a GoogleSignInClient with the options specified by gso.
        mGoogleSignInClient = GoogleSignIn.getClient(this, gso);
        findViewById(R.id.sign_in_button).setOnClickListener(this);

        // forgot password
        mForgotPasswordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, ResetPasswordActivity.class));
            }
        });

    }

    // get the views from the layout based on an unique id defined in the xml file
    private void initView() {

        mEditTextEmail = findViewById(R.id.edittext_email);
        mEditTextPhone = findViewById(R.id.edittext_phone);
        mCheckBoxAccept = findViewById(R.id.checkbox_accept);
        mLogginButton = findViewById(R.id.loginButton);
        mForgotPasswordButton = findViewById(R.id.forgotPasswordButton);

        mEditTextEmail.setText("");
        mEditTextPhone.setText("");
    }

    @Override
    protected void onResume() {
        super.onResume();

        GOOGLE_AUTH = 0;

        mEditTextEmail.setText("");
        mEditTextPhone.setText("");
        if (mCheckBoxAccept.isChecked()) {
            mCheckBoxAccept.toggle();


        }

    }

    // validate the content from the email EditText
    private boolean isEmailValid() {
        String email = mEditTextEmail.getText().toString();
        if (EmailHelper.isEmailValid(email)) {
            mAuthentication.setEmail(email);
            return true;
        } else {
            mEditTextEmail.setError(getResources().getString(R.string.error_email_input));
            return false;
        }
    }

    // validate the content from the phone EditText
    private boolean isPhoneValid() {
        String phone = mEditTextPhone.getText().toString();
        if (phone != null && !phone.isEmpty()) {
            mAuthentication.setPhone(phone);
            return true;
        } else {
            mEditTextPhone.setError(getResources().getString(R.string.error_phone_input));
            return false;
        }
    }

    // check if the checkbox is checked
    private boolean isAccepted() {
        if (mCheckBoxAccept.isChecked()) {
            mAuthentication.setAccepted(true);
            return true;
        } else {
            /*Toast.makeText(MainActivity.this, getResources().getString(R.string
                    .error_is_accepted_input), Toast.LENGTH_SHORT).show();*/

            if (mCheckBoxAccept.getVisibility() == View.GONE) {
                mAuthentication.setAccepted(true);
                return true;
            } else {
                AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(this);

                dlgAlert.setMessage("Terms and conditions should be accepted.");
                dlgAlert.setTitle("Authentication failed");
                dlgAlert.setPositiveButton("OK", null);
                dlgAlert.setCancelable(true);
                dlgAlert.create().show();

                dlgAlert.setPositiveButton("Ok",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {

                            }
                        });
                return false;
            }


        }
    }

    public void recyclerViewOnClick(View view) {
        if (isEmailValid() && isPhoneValid() && isAccepted()) {
            if (mLogginButton.getText().equals("SIGN IN")) {
                firebaseAuthWithEmail();
            }
            else {
                String email = mEditTextEmail.getText().toString();
                String password = mEditTextPhone.getText().toString();

                mAuth.createUserWithEmailAndPassword(email, password)
                        .addOnCompleteListener(MainActivity.this, task -> {

                            if (!task.isSuccessful()) {
                                Toast.makeText(MainActivity.this, "ERROR",Toast.LENGTH_LONG).show();
                            }
                            else {
                                // successful sign up
                                startActivity(new Intent(MainActivity.this, EditProfileActivity.class));
                            }
                        });
            }
        }
    }

    protected void setGooglePlusButtonText(SignInButton signInButton, String buttonText) {
        // Find the TextView that is inside of the SignInButton and set its text
        for (int i = 0; i < signInButton.getChildCount(); i++) {
            View v = signInButton.getChildAt(i);

            if (v instanceof TextView) {
                TextView tv = (TextView) v;
                tv.setText(buttonText);
                return;
            }
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.sign_in_button:
                signIn();
                break;
        }
    }

    private void updateUI(FirebaseUser account) {
        if (account != null) {
//            startActivity(new Intent(MainActivity.this, ProductsActivity.class));

            Toast.makeText(MainActivity.this,
                    String.format("Hello, %s!", account.getEmail().substring(0, account.getEmail().indexOf("@"))),
                    Toast.LENGTH_LONG).show();

        }
        else {
            /*Toast.makeText(MainActivity.this,
                    String.format("Invalid email or password!"),
                    Toast.LENGTH_LONG).show();*/
            AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(this);

            dlgAlert.setMessage("Wrong password or username. Please, try again");
            dlgAlert.setTitle("Authentication failed");
            dlgAlert.setPositiveButton("OK", null);
            dlgAlert.setCancelable(true);
            dlgAlert.create().show();

            dlgAlert.setPositiveButton("Ok",
                    new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {

                        }
                    });

        }
    }

    private void signIn() {
        Intent signInIntent = mGoogleSignInClient.getSignInIntent();
        startActivityForResult(signInIntent, RC_SIGN_IN);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        // Result returned from launching the Intent from GoogleSignInApi.getSignInIntent(...);
        if (requestCode == RC_SIGN_IN) {
            Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
            try {
                // Google Sign In was successful, authenticate with Firebase
                GoogleSignInAccount account = task.getResult(ApiException.class);
                firebaseAuthWithGoogle(account);
            } catch (ApiException e) {
                // Google Sign In failed, update UI appropriately
                Log.w(TAG, "Google sign in failed", e);

                AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(this);

                dlgAlert.setMessage("Cannot establish connection with this Google account." +
                        " Please try again.");
                dlgAlert.setTitle("Authentication failed");
                dlgAlert.setPositiveButton("OK", null);
                dlgAlert.setCancelable(true);
                dlgAlert.create().show();

                dlgAlert.setPositiveButton("Ok",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int which) {

                            }
                        });
            }
        }
    }

    private void firebaseAuthWithEmail() {
        String email = mEditTextEmail.getText().toString();
        String password = mEditTextPhone.getText().toString();

        mAuth.signInWithEmailAndPassword(email, password)
                .addOnCompleteListener(this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if (task.isSuccessful()) {
                            // Sign in success, update UI with the signed-in user's information
                            Log.d(TAG, "signInWithEmail:success");
                            FirebaseUser user = mAuth.getCurrentUser();
                            updateUI(user);

//                            DatabaseReference databaseReference = FirebaseDatabase.getInstance().getReference();
//                            databaseReference.orderByChild("")

                            // todo  - sign in get data from db

                            //UserInformation userInformation = UserInformation.getInstance();

//                            startActivity(new Intent(MainActivity.this, ProductsActivity.class));
                            startActivity(new Intent(MainActivity.this, NavigationDrawerActivity.class));

                        } else {
                            // If sign in fails, display a message to the user.
                            Log.w(TAG, "signInWithEmail:failure", task.getException());
                            /*Toast.makeText(EmailPasswordActivity.this, "Authentication failed.",
                                    Toast.LENGTH_SHORT).show();*/
                            updateUI(null);
                        }
                    }
                });

    }

    private void firebaseAuthWithGoogle(GoogleSignInAccount acct) {
        Log.d(TAG, "firebaseAuthWithGoogle:" + acct.getId());

        AuthCredential credential = GoogleAuthProvider.getCredential(acct.getIdToken(), null);
        mAuth.signInWithCredential(credential)
                .addOnCompleteListener(this, task -> {
                    if (task.isSuccessful()) {
                        // Sign in success, update UI with the signed-in user's information
                        Log.d(TAG, "signInWithCredential:success");
                        FirebaseUser user = mAuth.getCurrentUser();
                        updateUI(user);

                        GOOGLE_AUTH = 1;
                        startActivity(new Intent(MainActivity.this, NavigationDrawerActivity.class));

                    } else {
                        // If sign in fails, display a message to the user.
                        Log.w(TAG, "signInWithCredential:failure", task.getException());
                        updateUI(null);
                    }
                });
    }

    public void loginMessageOnClick(View view) {
        TextView textView = view.findViewById(R.id.loginMessage);
        if(textView.getText().equals("Already a member?")) {
            mCheckBoxAccept.setVisibility(View.GONE);
            textView.setText("Don't have an account yet? Register now!");
            mLogginButton.setText("SIGN IN");
        }
        else {
            textView.setText("Already a member?");
            mLogginButton.setText("SIGN UP");
        }
    }
}
