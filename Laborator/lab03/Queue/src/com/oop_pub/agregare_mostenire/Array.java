package com.oop_pub.agregare_mostenire;

public class Array {
    static final int ERROR = Integer.MIN_VALUE;

    private int[] actualArray;

    public Array() {
        this(10);
    }

    Array(final int n) {
        actualArray = new int[n];
    }

    final int get(final int pos) {
        if (pos < 0 || pos >= actualArray.length) {
            return ERROR;
        }

        return actualArray[pos];
    }

    final int set(final int pos, final int val) {

        if (pos < 0 || pos >= actualArray.length) {
            return ERROR;
        }

        actualArray[pos] = val;

        return 0;
    }

    public String toString() {
        StringBuilder s = new StringBuilder("[");

        for (int i = 0; i < actualArray.length; i++) {
            s.append(actualArray[i]).append(" ");
        }

        return s + "]";
    }

    public static void main(final String[] args) {
        Array array = new Array(10);

        //*********** EXEMPLE DE ADAUGARE ******************

        // adaugare corecta
        if (array.set(4, 99) != Array.ERROR) {
            System.out.println(array);
        } else {
            System.out.println("Error adding value");
        }

        // adaugare incorecta
        if (array.set(11, 99) != Array.ERROR) {
            System.out.println(array);
        } else {
            System.out.println("Error adding value");
        }

        //*********** EXEMPLE DE OBTINERE ******************

        // obtinere corecta
        int val = array.get(4);
        if (val != Array.ERROR) {
            System.out.println(val);
        } else {
            System.out.println("Error retrieving value");
        }

        // obtinere incorecta
        val = array.get(11);
        if (val != Array.ERROR) {
            System.out.println(val);
        } else {
            System.out.println("Error retrieving value");
        }
    }
}
