package main;

public class Exercise3 {

    public static void main(String[] args) {

        try {
            System.out.println("Try");
            return;
        } catch (Exception e) {
            System.out.println("Catch");

        } finally {
            System.out.println("Finally");
        }
    }
}
