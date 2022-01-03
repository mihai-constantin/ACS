package exercise2;

public class MyVector3 implements Sumabil {

    private int x;
    private int y;
    private int z;

    public MyVector3(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }

    @Override
    public void addValue(Sumabil value) {
        MyVector3 vector3 = (MyVector3) value;

        x += vector3.x;
        y += vector3.y;
        z += vector3.z;
    }

    @Override
    public int sum() {
        return x + y + z;
    }

    @Override
    public void print() {
        System.out.println("vector: " + x + " " + y + " " + z);
    }
}
