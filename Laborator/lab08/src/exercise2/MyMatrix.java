package exercise2;

public class MyMatrix implements Sumabil {

    private int[][] matrix = new int[4][4];

    public MyMatrix(int[][] matrix) {
        this.matrix = matrix;
    }

    @Override
    public void addValue(Sumabil value) {
        MyMatrix matrix = (MyMatrix) value;

        for (int i = 0; i < matrix.matrix.length; i++) {
            for (int j = 0; j < matrix.matrix[i].length; j++) {
                this.matrix[i][j] += matrix.matrix[i][j];
            }
        }

    }

    @Override
    public int sum() {
        int s = 0;

        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                s += matrix[i][j];
            }
        }

        return s;
    }

    @Override
    public void print() {
        System.out.println("Matrix");
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }

    }
}
