package main;

import java.util.ArrayList;
import java.util.List;

public class Exercise1 {

    public static void stack(){

        try {
            stack();
        } catch (StackOverflowError e) {
            System.out.println("Full stack");
        }
    }

    public static void heap(){

        try {
            List<Integer> array = new ArrayList<>(Integer.MAX_VALUE);
            System.out.println("Mai e loc in heap");
        } catch (OutOfMemoryError e){
            System.out.println("Full heap");
        }


    }

    public static void main(String[] args) {

        stack();
        heap();
    }
}
