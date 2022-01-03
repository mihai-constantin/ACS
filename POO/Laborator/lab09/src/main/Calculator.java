package main;

import java.util.Collection;

public class Calculator {

    public static Integer add (final Integer a, final Integer b) {

        try {
            Integer s = a + b;

            if(s < 0){
                throw new OverflowException();
            }

            if(s > 0){
                throw new UnderflowException();
            }

        } catch (OverflowException e) {
            System.out.println("OverflowException");
        }
        catch (UnderflowException e){
            System.out.println("UnderflowException");
        }

        return a + b;
    }

    public static Integer divide(final Integer a, final Integer b) {

        return a / b;
    }

    public static Integer average(Collection<Integer> collection) {

        Integer s = new Integer(0);

        for (Integer integer : collection) {
            s = add(s, integer);
        }

        return s / collection.size();
    }

    public static void main(String[] args) {

        Integer result = add(10, Integer.MAX_VALUE - 2);
        System.out.println(result);

        result = add(-1, Integer.MIN_VALUE);
        System.out.println(result);
    }


}
