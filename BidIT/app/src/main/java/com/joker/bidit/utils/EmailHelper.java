package com.joker.bidit.utils;

import android.text.TextUtils;
import android.util.Patterns;

public class EmailHelper {

    // checks if the email respects the email address pattern
    public static boolean isEmailAddressPattern(String email) {
        return (!TextUtils.isEmpty(email) && Patterns.EMAIL_ADDRESS.matcher(email).matches());
    }

    // checks if the email is not null and respects the email address pattern
    public static boolean isEmailValid(String email) {
        if (email != null && isEmailAddressPattern(email)) {
            return true;
        } else {
            return false;
        }
    }
}
