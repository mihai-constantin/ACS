package main;

import java.io.*;
import java.util.*;

/* Your class should be named SgInstance. */
public class SgInstance {
    /* Enter your code here. */

    private static SgInstance instance = null;

    private SgInstance() {

    }

    public static SgInstance getInstance() {
        if (instance == null) {
            instance = new SgInstance();
        }
        return instance;
    }


    /* DO NOT MODIFY */
    public static void main(String[] args) {
        SgInstance instance = getInstance();
        SgInstance instance2 = getInstance();
        System.out.println(instance != null && instance == instance2);
    }
}