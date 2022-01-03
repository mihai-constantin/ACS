package exercise1;

public class Main {

    public static void main(String[] args){


        Persoana p1 = new Persoana("Misu", 20, 3.93);
        Persoana p2 = new Persoana("Oana", 19, 3.80);
        Persoana p3 = new Persoana("Alexandra", 20, 3.75);
        Persoana p4 = new Persoana("Vann", 20, 4);

        MyHashMap<Persoana, Integer> myHashMap = new MyHashMap<Persoana, Integer>();

        myHashMap.init();

        myHashMap.put(p1, 1);
        myHashMap.put(p2, 2);
        myHashMap.put(p3, 3);
        myHashMap.put(p4, 4);

        myHashMap.printHashTable();
    }
}
