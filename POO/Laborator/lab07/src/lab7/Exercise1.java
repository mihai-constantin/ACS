package lab7;

import java.util.*;

public class Exercise1 {

    Collection<String> c = new LinkedHashSet<String>();

    public static void main(String[] args) {

        String[] names = {"Misu", "Oana", "Damian", "Rares", "Alexandra", "Gabi"};

        Random generator = new Random();

        for(int i = 0; i < names.length; i++){
            int value = generator.nextInt(names.length);

            if(c.contains(names[value])){
                System.out.println(names[value] + " is already in this collection");
            }

            c.add(names[value]);
        }

        System.out.println("=====   Collection   =====");
        for (String s : c) {
            System.out.println(s);
        }

    }
}
