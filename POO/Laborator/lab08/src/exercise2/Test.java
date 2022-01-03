package exercise2;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class Test {

    public <T extends Collection<Sumabil>> int sum(T collection) {

        int s = 0;
        for (Sumabil value : collection) {
            s += value.sum();
        }

        return s;
    }

    public static void main(String[] args) {

        Test test = new Test();

        MyVector3 vector1 = new MyVector3(1, 2, 3);
        MyVector3 vector2 = new MyVector3(5, 12, 4);
        MyVector3 vector3 = new MyVector3(6, 7, 8);

        MyMatrix matrix1 = new MyMatrix
                (new int[][]{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}});
        MyMatrix matrix2 = new MyMatrix
                (new int[][]{{13, 14, 15, 16}, {9, 10, 11, 12}, {5, 6, 7, 8}, {1, 2, 3, 4}});

        List<Sumabil> collection = new ArrayList<>();

        collection.add(vector1);
        collection.add(vector2);
        collection.add(vector3);
        collection.add(matrix1);
        collection.add(matrix2);

        /**
         * Adaug la vector2, valorile lui vector1.
         */
        vector2.addValue(vector1);

        /**
         * Adaug la matrix1, valorile lui matrix2.
         */
        matrix1.addValue(matrix2);

        for (Sumabil value : collection) {
            value.print();
            System.out.println();
        }

        System.out.println("sumOfElements: " + test.sum(collection));

    }
}
