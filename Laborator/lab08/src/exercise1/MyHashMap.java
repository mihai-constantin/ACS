package exercise1;

import java.util.ArrayList;
import java.util.List;

public class MyHashMap<K, V> {

    class Entry <K, V> {
        K key;
        V value;

        public Entry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return "{" +
                    "key=" + key +
                    ", value=" + value +
                    '}';
        }
    }

    private final static int DIMENSION = 50;

    public static int getDIMENSION() {
        return DIMENSION;
    }

    List<List<Entry<K, V>>> hashTable = new ArrayList<>(DIMENSION);

    public void init(){
        for(int i = 0; i < DIMENSION; i++) {
            List<Entry<K, V>> entries = new ArrayList<Entry<K, V>>();
            hashTable.add(entries);
        }
    }


    public void put(K key, V value) {

        Entry<K, V> entry = new Entry<K, V>(key, value);

        int hashCode = key.hashCode();
        hashTable.get(hashCode).add(entry);
    }

    public V get(K key){
        int hashCode = key.hashCode();

        System.out.println("hashCode = " + hashCode);

        List<Entry<K, V>> entries = hashTable.get(hashCode);

        for(Entry entry : entries){
            if(entry.key.equals(key)){
                return (V) entry.value;
            }
        }

        return null;
    }

    public void printHashTable(){
        for(int i = 0; i < DIMENSION; i++){
            List<Entry<K, V>> currentList = hashTable.get(i);

            System.out.println("#" + i + ": ");

            for(int j = 0; j < currentList.size(); j++){
                System.out.println(currentList.get(j));
            }

            System.out.println();
        }
    }
}
